<?php

/**
 * @file
 * Defines the Add Member panels pane.
 */

$plugin = array(
  'title' => t('Add Content Wizard'),
  'description' => t('Add content via a wizard popup.'),
  'single' => TRUE,
  'category' => t('Open Atrium'),
  'edit form' => 'oa_wizard_add_content_edit_form',
  'render callback' => 'oa_wizard_add_content_render',
  'defaults' => array(
    'content_types' => '',
    'button_class' => '',
    'title_prefix' => '',
  ),
);


/**
 * Render callback for the content visibility panel.
 */
function oa_wizard_add_content_render($subtype, $conf, $args, $context = NULL) {
  ctools_include('modal');
  ctools_modal_add_js();

  $nodes = $conf['content_types'];

  $links = array();
  $class = !empty($conf['button_class']) ? $conf['button_class'] : '';
  if (strpos($class, 'btn') !== FALSE) {
    if (strpos($class, 'btn-') === FALSE) {
      // handle default buttons in bootstrap 3
      $class .= ' btn-default';
    }
  }

  $custom_style = array(
    'oa-wizard' => array(
      'modalSize' => array(
        'type' => 'scale',
        'width' => 0.5,
        'height' => 0.5,
      ),
      'animation' => 'fadeIn',
    ),
  );

  ctools_include('ajax');

  drupal_add_js($custom_style, 'setting');

  $prefix = !empty($conf['title_prefix']) ? $conf['title_prefix'] : '';
  foreach ($nodes as $node_type) {
    $node = node_type_load($node_type);
    if (is_object($node) && node_access('create', $node_type)) {
      $links[] = '<li>' .
        ctools_modal_text_button($prefix . $node->name, 'api/oa_wizard/add/' . str_replace('_', '-', $node_type),
          $prefix . $node->name, $class . ' ctools-modal-oa-wizard')
        . '</li>';
    }
  }
  $output = '<ul>' . implode($links) . '</ul>';

  $block = new stdClass();
  $block->title = t('Create content');
  $block->content = $output;

  if (!empty($links)) {
    return $block;
  }
  return FALSE;
}

/**
 * Edit form for the panel.
 */
function oa_wizard_add_content_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $nodes = node_type_get_types();

  $options = array();
  foreach ($nodes as $node) {
    $options[$node->type] = check_plain($node->name);
  }
  $form['content_types'] = array(
    '#title' => t('Enable content types'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => isset($conf['content_types']) ? $conf['content_types'] : array_values($options),
    '#description' => t('Select which content types you wish to display Add buttons for.'),
  );

  $form['button_class'] = array(
    '#title' => t('CSS class for links'),
    '#type' => 'textfield',
    '#default_value' => $conf['button_class'],
    '#description' => 'Enter CSS class for links, such as btn.'
  );

  $form['title_prefix'] = array(
    '#title' => t('Title Prefix'),
    '#type' => 'textfield',
    '#default_value' => $conf['title_prefix'],
    '#description' => 'Enter prefix text for link titles.'
  );

  return $form;
}

/**
 * Submit handler for edit form. Save the custom form fields we added.
 */
function oa_wizard_add_content_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

