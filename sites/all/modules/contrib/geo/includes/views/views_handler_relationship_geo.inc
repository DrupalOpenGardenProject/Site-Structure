<?php // $Id: views_handler_relationship_geo.inc,v 1.2 2009/12/21 17:29:55 vauxia Exp $

class views_handler_relationship_geo extends views_handler_relationship {
  function query() {
    // Hard-code our own join handler.
    return parent::query();
  }
}

?>
