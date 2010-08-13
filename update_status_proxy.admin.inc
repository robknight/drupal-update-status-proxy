<?php
// $Id$

/**
 * @file
 * Admin include file.
 * 
 * @author Rob Knight <mail@robknight.org.uk>
 */

/**
 * Displays the form for the standard settings tab.
 *
 * @return
 *   array A structured array for use with Forms API.
 */
function update_status_proxy_admin_settings() {
  
  $form = array();
  
  $form['update_status_proxy_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Update Status Proxy'),
    '#default_value' => variable_get('update_status_proxy_enabled', 0),
    '#description' => t('Tell Drupal to use the proxy URL for updates')
  );
  
  $form['proxy_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Proxy Settings'),
    '#collapsed' => FALSE,
    '#tree' => FALSE
  );
  
  $form['proxy_settings']['update_status_proxy_proxy_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Proxy Hostname'),
    '#default_value' => variable_get('update_status_proxy_proxy_host', '')
  );
  
  $form['proxy_settings']['update_status_proxy_proxy_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Proxy Port'),
    '#default_value' => variable_get('update_status_proxy_proxy_port', '')
  );
  
  $form['proxy_settings']['update_status_proxy_proxy_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Proxy User'),
    '#default_value' => variable_get('update_status_proxy_proxy_user', '')
  );
  
  $form['proxy_settings']['update_status_proxy_proxy_pass'] = array(
    '#type' => 'password',
    '#title' => t('Proxy Password'),
    '#default_value' => variable_get('update_status_proxy_proxy_pass', '')
  );
  
  $form['update_status_proxy_update_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Default fetch URL for drupal.org updates'),
    '#default_value' => variable_get('update_status_proxy_update_url', UPDATE_DEFAULT_URL)
  );

  
  $form['#submit'][] = 'update_status_proxy_admin_settings_submit';
  $form['#validate'][] = 'update_status_proxy_admin_settings_validate';
  
  return system_settings_form($form);
}

/**
 * Validation handler for update status proxy admin settings form
 */
function update_status_proxy_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['update_status_proxy_proxy_port'] == '') {
    $form_state['values']['update_status_proxy_proxy_port'] = 8080;
  }
  
  if (!is_numeric($form_state['values']['update_status_proxy_proxy_port'])) {
    form_set_error('update_status_proxy_proxy_port', t('Proxy port must be a number'));
  }
}

/**
 * Submit handler for update status proxy admin settings form
 */
function update_status_proxy_admin_settings_submit($form, &$form_state) {
  if ($form_state['values']['update_status_proxy_enabled'] != variable_get('update_status_proxy_status', 0)) {
    if ($form_state['values']['update_status_proxy_enabled'] == 1) {
      update_status_proxy_enable();
      
    } else {
      update_status_proxy_disable();
    }
  }
  
  if ($form_state['values']['update_status_proxy_enabled'] == 1) {
    if ($form_state['values']['update_status_proxy_proxy_host'] == '') {
      drupal_set_message(t('Update Status Proxy is enabled but requires a proxy server to be set to operate properly'), 'warning');
    } else {
      
      if (!($sock = @fsockopen($form_state['values']['update_status_proxy_proxy_host'], 
                               $form_state['values']['update_status_proxy_proxy_port'], $errno, $errstr, 15))) {
        drupal_set_message(t('Could not connect to proxy server. Please check that proxy server details are correct.'), 'warning');
      } else {
        fclose($sock);
      }
    }
  }
}