<?php
/**
 * @file
 * oa_wizard.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function oa_wizard_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'oa_wizard-wizard-field_wizard_steps'
  $field_instances['oa_wizard-wizard-field_wizard_steps'] = array(
    'bundle' => 'wizard',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Steps for the wizard',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'oa_wizard',
    'field_name' => 'field_wizard_steps',
    'label' => 'Wizard Steps',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Steps for the wizard');
  t('Wizard Steps');

  return $field_instances;
}
