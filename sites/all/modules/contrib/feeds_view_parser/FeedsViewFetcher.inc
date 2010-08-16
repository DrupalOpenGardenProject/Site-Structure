<?php
// $Id: FeedsViewFetcher.inc,v 1.11 2010/06/22 18:45:17 adityakg Exp $

/**
 * @file Implementation of View Fetcher (dummy Fetcher)
 */

/**
 * Definition of the import batch object created on the fetching stage by
 * FeedsViewFetcher.
 * @package feeds
 * @author aditya
 */
class FeedsViewBatch extends FeedsImportBatch {
  protected $view_name;
  protected $display_id;

  /**
   * Constructor.
   */
  public function __construct($view_details) {
    // Tokenize the options
    $this->view_name = trim(strtok($view_details, ','));
    $this->display_id = trim(strtok(' '));
    
    parent::__construct();
  }

  /**
   * Implementation of FeedsImportBatch::getRaw();
   */
  public function getRaw() {
    // @todo check for error in views, throw exception if there is error.
    // @todo delete this, because this functionality will be implemented in the parser.
    
    if (!isset($this->raw)) {
      $this->raw = views_get_view_result($this->view_name, $this->display_id);
    }
    
    return $this->raw;
  }
  
  /**
   * Get the view name stored in the FeedsImportBatch
   */
  public function getViewName() {
    return $this->view_name;
  }
  
  /**
   * Get the view display id stored in the FeedsImportBatch
   */
  public function getDisplayId() {
    return $this->display_id;
  }
}
 
class FeedsViewFetcher extends FeedsFetcher {
  protected $batch;
  
  /**
   * The FeedsImportBatch might need to be retrieved more than once.
   * Thus, provide a variable in the Fetcher class that contain the
   * FeedsImportBatch object
   */
  public function fetch(FeedsSource $source) {
    if (!isset($batch)) {
      $source_config = $source->getConfigFor($this);
      $batch = new FeedsViewBatch($source_config['source']);
    }
    return $batch;
  }
  
  /**
   * Get the batch file
   * This function must be called only after fetch() has been called.
   */
  public function getBatch() {
    return $batch;
  }
}