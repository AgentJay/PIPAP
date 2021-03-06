<?php
/**
 * This file contains all the constants used in the module for
 * connecting to the ECAS server.
 */

$use_shared_fpfis = variable_get('ecas_use_shared_fpfis', FALSE);
if($use_shared_fpfis){
  // Point to the shared FPFIS library
  if ( !defined('FPFIS_COMMON_LIBRARIES_PATH') ) define('FPFIS_COMMON_LIBRARIES_PATH','/home/fpfis/util/libraries');  

} else {
  // Point to the local FPFIS library
  if ( !defined('FPFIS_COMMON_LIBRARIES_PATH') ) define ('FPFIS_COMMON_LIBRARIES_PATH', drupal_get_path('module', 'ecas') . '/libraries');
  if ( !defined('FPFIS_SERVER_HOSTNAME') ) define('FPFIS_SERVER_HOSTNAME','');
  if ( !defined('FPFIS_SERVER_PORT') ) define('FPFIS_SERVER_PORT','');

  /////////////////////////////////////////////////////////////////////////////////////////
  // IMPORTANT: REMOVE TESTING SETTING BELOW
  /*
  if ( !defined('FPFIS_ECAS_URL') ) define('FPFIS_ECAS_URL', 'ecast.cc.cec.eu.int');
  if ( !defined('FPFIS_ECAS_URI') ) define('FPFIS_ECAS_URI', '/cas');

  if ( !defined('FPFIS_LDAP_SERVER_NAME') ) define('FPFIS_LDAP_SERVER_NAME', 'cedtest.cec.eu.int');
  if ( !defined('FPFIS_LDAP_SERVER_PORT') ) define('FPFIS_LDAP_SERVER_PORT', '10389');
  if ( !defined('FPFIS_LDAP_BASE_DN') ) define('FPFIS_LDAP_BASE_DN', 'ou=People,o=cec.eu.int');
  if ( !defined('FPFIS_LDAP_BASE_DN_DG') ) define('FPFIS_LDAP_BASE_DN_DG', 'ou=Groups,o=cec.eu.int');
  if ( !defined('FPFIS_LDAP_USER_DN') ) define('FPFIS_LDAP_USER_DN', '');
  if ( !defined('FPFIS_LDAP_PASSWORD') ) define('FPFIS_LDAP_PASSWORD', '');
  */
  // END OF TEST SETTINGS
  /////////////////////////////////////////////////////////////////////////////////////////
  
}

// Load the fpfis library
/*USELESS ALREADY DONE IN THE MODULE ! */
/*
if ( is_file(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/fpfis_common.php') ) {
  include_once(FPFIS_COMMON_LIBRARIES_PATH . '/FPFIS_Common/fpfis_common.php');
}
*/
/* Defines default values for various parameters */
define('ECAS_DEFAULT_ASSURANCE_LEVEL', 'LOW');
define('ECAS_DEFAULT_DOMAIN', '');
define('ECAS_DEFAULT_ACCOUNT_REQUEST_URL', 'https://ecas.ec.europa.eu/cas/eim/external/register.cgi?service=%local_ecas_url%');
define('ECAS_DEFAULT_CHANGE_PASSWORD_URL', 'https://ecas.ec.europa.eu/cas/init/passwordResetRequest.cgi');

define('ECAS_DEFAULT_DEBUG_LOGPATH', 'phpCas.log');

define('ECAS_DEFAULT_LOGIN_MESSAGE', 'Logged in via ECAS as %ecas_username.');
define('ECAS_DEFAULT_WARNING_MESSAGE', 'Your account is not yet approved');
define('ECAS_DEFAULT_MAIL_ADDRESS', 'unknown.mail@address.net');

define('ECAS_DEFAULT_PROFILE_FIRSTNAME_FIELD', 'field_firstname');
define('ECAS_DEFAULT_PROFILE_LASTNAME_FIELD',  'field_lastname');
define('ECAS_DEFAULT_PROFILE_ECAS_MAIL_FIELD', 'field_ecas_mail');

define('ECAS_NO_LOGIN', 0);
define('ECAS_LOGIN',    1);
define('ECAS_GATEWAY',  2);

define('ECAS_DEFAULT_PAGES', '');
define('ECAS_LOGIN_EXLUDE_PAGES', 0);
define('ECAS_LOGIN_INCLUDE_PAGES', 1);
