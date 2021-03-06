<?php
/**
 * @file
 * Callbacks used by the administration area.
 */

/**
 * Generates the cache purge rule editing form.
 */
function nexteuropa_varnish_cache_purge_rule_form($form, &$form_state, $purge_rule, $op = 'edit', $entity_type = NULL) {
  $form['content_type'] = array(
    '#title' => t('Content Type'),
    '#type' => 'select',
    '#empty_option' => '',
    '#options' => node_type_get_names(),
    '#default_value' => isset($purge_rule->content_type) ? $purge_rule->content_type : '',
    '#required' => TRUE,
  );

  $form['paths'] = array(
    '#title' => t('Paths'),
    '#type' => 'textarea',
    '#default_value' => isset($purge_rule->paths) ? $purge_rule->paths : '',
    '#required' => TRUE,
    '#description' => _nexteuropa_varnish_paths_description(),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Get the description for the purge paths field.
 *
 * @return string
 *   Description for the field.
 */
function _nexteuropa_varnish_paths_description() {
  $wildcard_descriptions = array(
    t('* (asterisk) matches any number of any characters including none'),
    t('? (question mark) matches any single character'),
  );

  $description = '<p>' . t('Paths to purge. One per line. The paths should be relative to the base URL. Use / for the front page.') . '</p>';

  $description .= '<p>' . t('You can use the following wildcard patterns:') . '</p>';

  $wildcard_description = array(
    '#theme' => 'item_list',
    '#type' => 'ul',
    '#items' => $wildcard_descriptions,
  );

  $description .= drupal_render(
    $wildcard_description
  );

  $description .= '<p>' . t('In all cases above, the / (forward slash) will never be matched.') . '</p>';

  return $description;
}

/**
 * Form API submit callback for the cache purge rule editing form.
 */
function nexteuropa_varnish_cache_purge_rule_form_submit(&$form, &$form_state) {
  $purge_rule = entity_ui_form_submit_build_entity($form, $form_state);
  entity_save('nexteuropa_varnish_cache_purge_rule', $purge_rule);

  $form_state['redirect'] = 'admin/config/frontend_cache_purge_rules';
}
