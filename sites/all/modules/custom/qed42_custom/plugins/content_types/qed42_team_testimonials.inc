<?php

$plugin = array(
  'title' => t('Qed42 Team testimonials'),
  'single' => TRUE,
  'category' => array('QED42 Custom'),
  'edit form' => 'qed42_team_testimonials_form_edit',
  'render callback' => 'qed42_team_testimonials_render',
);

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */

function qed42_team_testimonials_render($subtype, $conf, $args, $context) {
  $block = new stdClass();

  //get the designation
  $designation = $conf['designation'];

  drupal_add_js(drupal_get_path('module', 'qed42_custom') . '/includes/js/text-slide.js');
  drupal_add_js(drupal_get_path('module', 'qed42_custom') . '/includes/js/jquery.innerfade.js');

  $users_query = new EntityFieldQuery();
  $result = $users_query->entityCondition('entity_type', 'user')
              ->fieldCondition('field_row_number', 'value', $designation, '=')
              ->execute();
  $variables['style_name'] = $image_size;
  while ($uid = array_shift($result['user'])->uid) {
    $users[] = user_load($uid);
  }

  foreach($users as $user) {
    $user_intro = "<div class='user-name'>--" . $user->field_full_name['und'][0]['value'] . "</div>";
    foreach ($user->field_testimonials['und'] as $testimonial) {
      $testimonials[] = $testimonial['value'] . $user_intro;
    }
  }

  $block->content = '<div id="user-testimonials">' . theme('item_list', array('items' => $testimonials)) . "</div>";
  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function qed42_team_testimonials_form_edit($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['designation'] = array(
    '#type' => 'textfield',
    '#title' => t('Row Id for the team members. @todo// to change the field to designation'),
    '#default_value' => isset($conf['designation']) ? $conf['designation'] : '',
  );

  return $form;
}

/**
 * 'Edit form' callback for the content type.
 */
function qed42_team_testimonials_form_edit_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
