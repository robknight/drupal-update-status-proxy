//$Id$

Description
-----------

Update Status Proxy is a module which provides a work-around for Drupal's
inability to handle proxy servers, which makes getting the update status of
modules impossible when your site is behind a restrictive firewall.

It works by providing a local endpoint which proxies the request through to the
original source of the update status information, via a proxy server of the
user's choice.

Installation
------------

Enable the module and follow the on-screen instructions. You will need to know
the details of your proxy server.