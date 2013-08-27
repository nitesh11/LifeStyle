<?php

$plugin = array(
  'title' => t('Qed42 Team Members'),
  'single' => TRUE,
  'category' => array('QED42 Custom'),
  'edit form' => 'qed42_team_members_form_edit',
  'render callback' => 'qed42_team_members_form_render',
);

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */

function qed42_team_members_form_render($subtype, $conf, $args, $context) {
  $block = new stdClass();

  //get the designation
  $designation = $conf['designation'];

  // get the image size
  $image_size = isset($conf['picture_size'])? $conf['picture_size'] : 'thumbnail';

  $users_query = new EntityFieldQuery();
  $result = $users_query->entityCondition('entity_type', 'user')
              ->fieldCondition('field_row_number', 'value', $designation, '=')
              ->execute();
  $variables['style_name'] = $image_size;
  while ($uid = array_shift($result['user'])->uid) {
    $users[] = user_load($uid);
  }
  foreach($users as $user) {
    $variables['path'] = ($user->picture != NULL) ? $user->picture->uri : variable_get('user_picture_default', '');
    $user_full_name_markup = l($user->field_full_name['und'][0]['value'], 'user/' . $user->uid, array('attributes' => array('class' => array('user-profile-link'))));
    $images[] = theme('image_style', $variables, 'user/' . $user->uid, $options = array('html' => TRUE)) . $user_full_name_markup;
  }

  $block->content = theme('item_list', array('items' => $images));
  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function qed42_team_members_form_edit($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['designation'] = array(
    '#type' => 'textfield',
    '#title' => t('Row Id for the team members. @todo// to change the field to designation'),
    '#default_value' => isset($conf['designation']) ? $conf['designation'] : '',
  );

  $form['picture_size'] = array(
    '#title' => t('Image size'),
    '#type' => 'select',
    '#description' => t('Please select the image size to be display'),
    '#default_value' => !empty($conf['picture_size']) ? $conf['picture_size'] : '',
    '#options' => _cover_image_size(),
  );

  return $form;
}

/**
 * 'Edit form' callback for the content type.
 */
function qed42_team_members_form_edit_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Helper function to get all presets.
 */
function _cover_image_size() {
 foreach (image_styles() as $key => $val) {
    $image_size[$key] = $key;
  }

  return $image_size;
}
