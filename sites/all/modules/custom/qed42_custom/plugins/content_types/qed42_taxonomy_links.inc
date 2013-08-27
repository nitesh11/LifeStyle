<?php

$plugin = array(
  'title' => t('Qed42 Work taxonomy links'),
  'single' => TRUE,
  'category' => array('QED42 Custom'),
  'edit form' => 'qed42_taxonomy_links_form_edit',
  'render callback' => 'qed42_taxonomy_links_form_render',
);

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */

function qed42_taxonomy_links_form_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $vocab = isset($conf['vocab']) ? $conf['vocab'] : '';

  if ($vocab) {
    $terms = taxonomy_get_tree($vocab);
    $term_links[] = l($conf['text_all'], $conf['link_all'], array('attributes' => array('class' => array('taxonomy-link'))));
    $term_links[] = '<span class="f-slash"></span>';
    foreach ($terms as $key => $term) {
      $term_links[] = l($term->name, drupal_get_path_alias('taxonomy/term/' . $term->tid), array('attributes' => array('class' => array('taxonomy-link'))));
      $term_links[] = '<span class="f-slash"></span>';
    }
  }

  $block->content = theme('item_list', array('items' => $term_links, 'attributes' => array('class' => array('taxonomy-link-list'))));
  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function qed42_taxonomy_links_form_edit($form, &$form_state) {
  $conf = $form_state['conf'];
  $vocabs = taxonomy_get_vocabularies();  
  foreach ($vocabs as $vid => $vocab) {
    $options[$vid] = $vocab->name;
  }

  $form['vocab'] = array(
    '#type' => 'select',
    '#title' => t('Vocabulary for which term-links should be rendered'),
    '#default_value' => isset($conf['vocab']) ? $conf['vocab'] : '',
    '#options' => $options,
  );

  $form['text_all'] = array(
    '#type' => 'textfield',
    '#title' => t('Text for all terms links'),
    '#default_value' => isset($conf['text_all']) ? $conf['text_all'] : '',
  );

  $form['link_all'] = array(
    '#type' => 'textfield',
    '#title' => t('Link for all terms page'),
    '#default_value' => isset($conf['link_all']) ? $conf['link_all'] : '',
  );
  return $form;
}

/**
 * 'Edit form' callback for the content type.
 */
function qed42_taxonomy_links_form_edit_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
