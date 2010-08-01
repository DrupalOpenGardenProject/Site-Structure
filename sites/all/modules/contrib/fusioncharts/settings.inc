<?php
// $Id: settings.inc,v 1.3.2.2 2009/03/05 08:03:39 aaron1234nz Exp $ 

/**
 * @file
 * Contains the form definition for the settings of each type of chart
 */
 
function _fusioncharts_settings_subform($chart_type, $obj) {
  $form = array();
  if (empty($obj->settings)) {
    $obj->settings = fusioncharts_settings('fusioncharts-defset'); //load up some sensible default values
  }
  if (empty($obj->attributes)) {
    $obj->attributes = fusioncharts_settings('fusioncharts-defattr'); //load up some sensible default values
  }
  switch ($chart_type) {
    //Single Series Charts
    case 'Column 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_h($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Column 3D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;    
          
    case 'Pie 3D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_c($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_PieProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_PieProperties_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Pie 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_c($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_PieProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_PieShadowProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NameValuedisplaydistance($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NameValuedisplaydistance_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Line 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_LineProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_LineShadowProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Anchor($obj->attributes));
      break;
      
    case 'Bar 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_d($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Area 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Area($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
        
    case 'Doughnut 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_c($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_PieProperties2($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_PieShadowProperties2($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NameValuedisplaydistance($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
            
    case 'Multi-series Column 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_h($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Multi-series Column 3D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));  
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
              
    case 'Multi-series Line 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_LineProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Anchor($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Multi-series Bar 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_d($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Multi-series Area 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Area($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case ''://?? don't know what this set if for.  I lost track.
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;    
              
    case 'Stacked Column 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_h($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Stacked Area 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Area($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Stacked Column 2D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_d($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_h($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;

    case 'Stacked Column 3D':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    // Combination Charts
    case 'Multi-series Column 3D + Line - Dual Y Axis':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra2($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits2($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_f($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_e($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_LineProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_LineShadowProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Anchor($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Multi-series Column 2D + Line - Dual Y Axis':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra2($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits2($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_b($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_h($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_f($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ZeroPlane($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_LineProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_LineShadowProperties($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Anchor($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Candlestick Chart':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumericalLimits3($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalH($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_divisionalV($obj->attributes));
      //$form = array_merge_recursive($form, _fusioncharts_Candle($obj->settings)); 
      break;
      
    case 'Funnel Chart':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_a($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_i($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_ChartMargins($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_NumberFormatting($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Colors($obj->attributes));
      break;
      
    case 'Gantt Chart':
      $form = array_merge_recursive($form, _fusioncharts_Titles($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Titles_extra($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Background($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Canvas($obj->settings)); 
      $form = array_merge_recursive($form, _fusioncharts_GenericProperties_j($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_Font($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_HoverCaption($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_GanttGeneral($obj->settings));
      $form = array_merge_recursive($form, _fusioncharts_DataTable($obj->attributes));
      break;
  }
  return $form;
}

function _fusioncharts_Background($settings) {
  $form['settings']['background'] = array(
    '#type' => 'fieldset',
    '#title' => t('Background Properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['background']['bgcolor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Background Color'),
    );
  $form['settings']['background']['bgcolor'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($settings['bgcolor'] ? $settings['bgcolor'] : '#f3f3f3'),
    '#colorpicker' => 'settings_background_bgcolor_colorpicker',
    '#description' => t('The background color for the chart.'),
    );
  $form['settings']['background']['bgAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Background transparency'),
    '#default_value' =>  ($settings['bgAlpha'] ? $settings['bgAlpha'] : '70'),
    '#description' => t('The background transparency of the graph (0-100).'),
    '#size' => 5, 
    );
  $form['settings']['background']['bgSWF'] = array(
    '#type' => 'textfield',
    '#title' => t('Background Shockwave file'),
    '#default_value' =>  ($settings['bgSWF'] ? $settings['bgSWF'] : ''),
    '#description' => t('Path to an external .swf file.  Use this to set the background of the chart to be a shockwave file.'),
    '#size' => 60, 
    );
  return $form;
}
function _fusioncharts_Canvas($settings) {
  $form['settings']['canvas'] = array(
    '#type' => 'fieldset',
    '#title' => t('Canvas Properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['canvas']['canvasBgColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Canvas Color'),
    );
  $form['settings']['canvas']['canvasBgColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($settings['canvasBgColor'] ? $settings['canvasBgColor'] : '#f3fff3'),
    '#colorpicker' => 'settings_canvas_canvasBgColor_colorpicker',
    '#description' => t('The background color of the canvas.'),
    );
  $form['settings']['canvas']['bgAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Background transparency'),
    '#default_value' =>  ($settings['bgAlpha'] ? $settings['bgAlpha'] : '70'),
    '#description' => t('The transparency of the canvas (1-100).'),
    '#size' => 5,
    );
  $form['settings']['canvas']['canvasBorderColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Canvas border color'),
    );
  $form['settings']['canvas']['canvasBorderColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The border color of the canvas.'),
    '#default_value' => ($settings['canvasBorderColor'] ? $settings['canvasBorderColor'] : '#000000'),
    '#colorpicker' => 'settings_canvas_canvasBorderColor_colorpicker',
    );
  $form['settings']['canvas']['canvasBorderThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Canvas border thickness'),
    '#default_value' =>  ($settings['canvasBorderThickness'] ? $settings['canvasBorderThickness'] : '1'),
    '#description' => t('The border thickness (in pixels) of the canvas.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_Canvas_extra($settings) {
  $form['settings']['canvas']['canvasBaseColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Canvas base color'),
    );
  $form['settings']['canvas']['canvasBaseColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color of the canvas base. (The canvas is what is behind the columns).'),
    '#default_value' => ($settings['canvasBaseColor'] ? $settings['canvasBaseColor'] : '#f3fff3'),
    '#colorpicker' => 'settings_canvas_canvasBaseColor_colorpicker',
    );
  $form['settings']['canvas']['canvasBaseDepth'] = array(
    '#type' => 'textfield',
    '#title' => t('Canvas base depth'),
    '#default_value' =>  ($settings['canvasBaseDepth'] ? $settings['canvasBaseDepth'] : ''),
    '#description' => t('The 3D Depth of the canvas base.'),
    '#size' => 5,
    );
  $form['settings']['canvas']['canvasBgDepth'] = array(
    '#type' => 'textfield',
    '#title' => t('3D Depth of the canvas background'),
    '#default_value' =>  ($settings['canvasBgDepth'] ? $settings['canvasBgDepth'] : ''),
    '#description' => t('The 3D Depth of the canvas background.'),
    '#size' => 5,
    );
  $form['settings']['canvas']['showCanvasBg'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the canvas background'),
    '#default_value' => $settings['showCanvasBg'],
    '#attributes' => ($settings['showCanvasBg'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['canvas']['showCanvasBase'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the canvas base'),
    '#default_value' => $settings['showCanvasBase'],
    '#attributes' => ($settings['showCanvasBase'] == 1 ? array('checked' => 'checked') : array()),
    );
  return $form;
}
function _fusioncharts_Titles($settings) {
  $form['settings']['titles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chart and Axis Titles'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    );
  $form['settings']['titles']['caption'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption'),
    '#default_value' => ($settings['caption'] ? $settings['caption'] : ''),
    '#description' => t('The caption that would appear at the top of the chart.'),
    );
  $form['settings']['titles']['subCaption'] = array(
    '#type' => 'textfield',
    '#title' => t('Sub caption'),
    '#default_value' => ($settings['subCaption'] ? $settings['subCaption'] : ''),
    '#description' => t('Sub-caption of the chart.'),
    );
  return $form;
}
function _fusioncharts_Titles_extra($settings) {
  $form['settings']['titles']['xAxisName'] = array(
    '#type' => 'textfield',
    '#title' => t('X-axis label'),
    '#default_value' => ($settings['xAxisName'] ? $settings['xAxisName'] : ''),
    '#description' => t('X-axis label.'),
    );
  $form['settings']['titles']['yAxisName'] = array(
    '#type' => 'textfield',
    '#title' => t('Y-axis label'),
    '#default_value' => ($settings['yAxisName'] ? $settings['yAxisName'] : ''),
    '#description' => t('X-axis label.'),
    );
  return $form;
}
function _fusioncharts_Titles_extra2($settings) {
  $form['settings']['titles']['xAxisName'] = array(
    '#type' => 'textfield',
    '#title' => t('X-axis label'),
    '#default_value' => ($settings['xAxisName'] ? $settings['xAxisName'] : ''),
    '#description' => t('X-axis label.'),
    );
  $form['settings']['titles']['PYAxisName'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary Y-axis'),
    '#default_value' => ($settings['PYAxisName'] ? $settings['PYAxisName'] : ''),
    '#description' => t('Primary Y-axis label.'),
    );
  $form['settings']['titles']['SYAxisName'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary Y-axis'),
    '#default_value' => ($settings['SYAxisName'] ? $settings['SYAxisName'] : ''),
    '#description' => t('Secondary Y-axis label.'),
    );
  return $form;
}  
function _fusioncharts_NumericalLimits($settings) {
  $form['settings']['numericallimits'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chart Numerial Limits'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['numericallimits']['yAxisMinValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Lower limit of the Y-axis'),
    '#default_value' => ($settings['yAxisMinValue'] ? $settings['yAxisMinValue'] : ''),
    '#description' => t('The minimum of Y-axis.'),
    );
  $form['settings']['numericallimits']['yAxisMaxValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Upper limit of the Y-axis'),
    '#default_value' => ($settings['yAxisMaxValue'] ? $settings['yAxisMaxValue'] : ''),
    '#description' => t('The maximum of Y-axis.'),
    );
  return $form;
}
function _fusioncharts_NumericalLimits2($settings) {
  $form['settings']['numericallimits'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chart Numerial Limits'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['numericallimits']['PYAxisMaxValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Upper limit of primary Y-axis.'),
    '#default_value' => ($settings['PYAxisMaxValue'] ? $settings['PYAxisMaxValue'] : ''),
    '#description' => t('The maximum of the primary Y-axis.'),
    );
  $form['settings']['numericallimits']['PYAxisMinValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Lower limit of primary Y-axis'),
    '#default_value' => ($settings['PYAxisMinValue'] ? $settings['PYAxisMinValue'] : ''),
    '#description' => t('The minimum of primary Y-axis.'),
    );
  $form['settings']['numericallimits']['SYAxisMaxValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Upper limit of secondary Y-axis.'),
    '#default_value' => ($settings['SYAxisMaxValue'] ? $settings['SYAxisMaxValue'] : ''),
    '#description' => t('The maximum of secondary Y-axis.'),
    );
  $form['settings']['numericallimits']['SYAxisMinValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Lower limit of secondary Y-axis'),
    '#default_value' => ($settings['SYAxisMinValue'] ? $settings['SYAxisMinValue'] : ''),
    '#description' => t('The mininum of secondary Y-axis.'),
    );
  return $form;
}
function _fusioncharts_NumericalLimits3($settings) {
  $form['settings']['numericallimits']['xAxisMinValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Lower limit of X-axis'),
    '#default_value' => ($settings['xAxisMinValue'] ? $settings['xAxisMinValue'] : ''),
    '#description' => t('The minimum of the X-axis.'),
    );
  $form['settings']['numericallimits']['xAxisMaxValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Upper limit of Y-axis'),
    '#default_value' => ($settings['xAxisMaxValue'] ? $settings['xAxisMaxValue'] : ''),
    '#description' => t('The maximum of the X-axis.'),
    );
  $form['settings']['numericallimits']['SYAxisMaxValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Upper limit of secondary Y-axis.'),
    '#default_value' => ($settings['SYAxisMaxValue'] ? $settings['SYAxisMaxValue'] : ''),
    '#description' => t('The maximum of the secondary Y-axis.'),
    );
  $form['settings']['numericallimits']['SYAxisMinValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Lower limit of secondary Y-axis'),
    '#default_value' => ($settings['SYAxisMinValue'] ? $settings['SYAxisMinValue'] : ''),
    '#description' => t('The minimum of the secondary Y-axis.'),
    );
  $form['settings']['numericallimits']['overRideLimitCalc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override limit calculation'),
    '#default_value' => $settings['showCanvasBase'],
    '#description' => t('When you provide data and the upper and lower limits to FusionCharts, FusionCharts (while rendering) checks whether the upper and lower limits are correctly provided - that is it checks whether all the data values fall within the specified range. Sometimes, this process takes a little extra time when you have a large amount of data. If in that case you don\'t want FusionCharts to cross check the limits explicitly provided by you, you can tick this box and then FusionCharts won\'t delve into the process of checking thus saving that extra bit of time required.'),
    '#attributes' => ($settings['showCanvasBase'] == 1 ? array('checked' => 'checked') : array()),
  );
  return $form;
}
function _fusioncharts_GenericProperties_a($settings) {
  $form['settings']['genericproperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Generic Properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['genericproperties']['shownames'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show names'),
    '#description' => t('Whether the X-axis values (for the data sets) will be displayed or not.'),
    '#attributes' => ($settings['shownames'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['showValues'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show values'),
    '#default_value' => ($settings['showValues']),
    '#description' => t('Whether the data numerical values will be displayed along with the columns, bars, lines and the pies.'),
    '#attributes' => ($settings['showValues'] == 1 ? array('checked' => 'checked') : array())
    );
  $form['settings']['genericproperties']['animation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Animation'),
    '#default_value' => ($settings['animation']),
    '#description' => t('This attribute sets whether the animation is to be played or whether the entire chart would be rendered at one go.'),
    '#attributes' => ($settings['animation'] == 1 ? array('checked' => 'checked') : array())
  );
  return $form;
}
function _fusioncharts_GenericProperties_b($settings) {
  $form['settings']['genericproperties']['showLimits'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show limits'),
    '#default_value' => $settings['showLimits'],
    '#description' => t('Whether to show/hide the chart limit textboxes.'),
    '#attributes' => ($settings['showLimits'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['rotateNames'] = array(
    '#type' => 'checkbox',
    '#title' => t('Rotate names'),
    '#default_value' => $settings['rotateNames'],
    '#description' => t('Whether the category name text boxes would be rotated or not.'),
    '#attributes' => ($settings['rotateNames'] == 1 ? array('checked' => 'checked') : array()),
    );
  return $form;
}
function _fusioncharts_GenericProperties_h($settings) {
  $form['settings']['genericproperties']['showColumnShadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Column shadow'),
    '#default_value' => $settings['showColumnShadow'],
    '#description' => t('Whether the 2D shadow for the columns would be shown or not.'),
    '#attributes' => ($settings['showColumnShadow'] == 1 ? array('checked' => 'checked') : array()),
    );

  return $form;
}
function _fusioncharts_GenericProperties_c($settings) {
  $form['settings']['genericproperties']['showPercentageValues'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show percentage values'),
    '#default_value' => $settings['showPercentageValues'],
    '#description' => t('If you\'ve opted to show the data value, this attribute helps you control whether to show percentage values or actual values.'),
    '#attributes' => ($settings['showPercentageValues'] == 1 ? array('checked' => 'checked') : array()),
  );
  $form['settings']['genericproperties']['showPercentageInLabel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show percentage in label'),
    '#default_value' => $settings['showPercentageInLabel'],
    '#description' => t('If you\'ve opted to show the data value, this attribute helps you control whether to show percentage values or actual values in the pie labels.'),
    '#attributes' => ($settings['showPercentageInLabel'] == 1 ? array('checked' => 'checked') : array()),
  );
  return $form;
}
function _fusioncharts_GenericProperties_d($settings) {
  $form['settings']['genericproperties']['showBarShadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show bar shadow'),
    '#default_value' => $settings['showBarShadow'],
    '#description' => t('Whether the 2D shadow for the bars would be shown or not.'),
    '#attributes' => ($settings['showBarShadow'] == 1 ? array('checked' => 'checked') : array()),
    );
  return $form;
}
function _fusioncharts_GenericProperties_e($settings) {
  $form['settings']['genericproperties']['showLegend'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Legend'),
    '#default_value' => $settings['showLegend'],
    '#description' => t('This attribute sets whether the legend would be displayed at the bottom of the chart.'),
    '#attributes' => ($settings['showLegend'] == 1 ? array('checked' => 'checked') : array()),
    );
  return $form;
}
function _fusioncharts_GenericProperties_f($settings) {
  $form['settings']['genericproperties']['showSecondaryLimits'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show secondary limits'),
    '#default_value' => $settings['showSecondaryLimits'],
    '#description' => t('Option whether to show/hide the chart limit textboxes (secondary Y-axis).'),
    '#attributes' => ($settings['showSecondaryLimits'] == 1 ? array('checked' => 'checked') : array()),
    );
  return $form;
}
function _fusioncharts_GenericProperties_i($settings) {
 /* 
  Transparency of individual slices is not implemented so this setting has no meaning 
  $form['settings']['genericproperties']['fillAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Transparency'),
    '#default_value' => ($settings['fillAlpha'] ? $settings['fillAlpha'] : ''),
    '#description' => t('This attribute helps you specify the transparency of the funnel chart as a whole, i.e., all the funnel segments would be shown in the transparency mentioned in this attribute.'),
    );
 */
  $form['settings']['genericproperties']['isSliced'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sliced'),
    '#default_value' => $settings['isSliced'],
    '#description' => t('his attribute specifies whether the the various funnel segments would be sliced, i.e., separated from each other by a distance.'),
    '#attributes' => ($settings['isSliced'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['slicingDistance'] = array(
    '#type' => 'textfield',
    '#title' => t('Slicing Distance'),
    '#default_value' => ($settings['slicingDistance'] ? $settings['slicingDistance'] : '10'),
    '#description' => t('This attribute specifies the distance (in pixels) by which the various funnel segments would be separated from each other by.'),
    );
  $form['settings']['genericproperties']['funnelBaseWidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Funnel base width'),
    '#default_value' => ($settings['funnelBaseWidth'] ? $settings['funnelBaseWidth'] : ''),
    '#description' => t('This attribute sets the width of the tap, i.e., the bottom part of the funnel.'),
    );
  $form['settings']['genericproperties']['funnelBaseHeight'] = array(
    '#type' => 'textfield',
    '#title' => t('Funnel base height'),
    '#default_value' => ($settings['funnelBaseHeight'] ? $settings['funnelBaseHeight'] : ''),
    '#description' => t(' This attribute sets the height of the tap of the funnel.'),
    );
  return $form;
}
function _fusioncharts_GenericProperties_j($settings) {
  $form['settings']['genericproperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Generic properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['genericproperties']['dateFormat'] = array(
    '#type' => 'select',
    '#title' => t('Date Format'),
    '#options' => array('mm/dd/yyyy' => 'mm/dd/yyyy', 'dd/mm/yyyy' => 'dd/mm/yyyy', 'yyyy/mm/dd' => 'yyyy/mm/dd'),
    '#default_value' => ($settings['dateFormat'] ? $settings['dateFormat'] : 'yyyy/mm/dd'),
    '#description' => t('This is the most important attribute, which you\'ll need to specify for all the Gantt charts that you build. With the help of this attribute, you\'re basically specifying the format in which you\'ll be providing your dates to FusionCharts.'),
    );
  $form['settings']['genericproperties']['animation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Animation'),
    '#default_value' => $settings['animation'],
    '#description' => t('Should the Gantt task bars should be animated or not.'),
    '#attributes' => ($settings['animation'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['showTaskStartDate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show task start date'),
    '#default_value' => $settings['showTaskStartDate'],
    '#description' => t('Whether the start date of each task will be shown on the left of the task bar.'),
    '#attributes' => ($settings['showTaskStartDate'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['showTaskEndDate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show task end date'),
    '#default_value' => $settings['showTaskEndDate'],
    '#description' => t('Whether the end date of each task will be shown on the right of the task bar.'),
    '#attributes' => ($settings['showTaskEndDate'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['showTaskNames'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show task names'),
    '#default_value' => $settings['showTaskNames'],
    '#description' => t('Whether the name of each task will be shown over the task bar.'),
    '#attributes' => ($settings['showTaskNames'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['taskDatePadding'] = array(
    '#type' => 'checkbox',
    '#title' => t('Task date padding'),
    '#default_value' => $settings['taskDatePadding'],
    '#description' => t('If you opt to show the task start or end date, this attribute lets you configure the distance between the date textbox and the task bar.'),
    '#attributes' => ($settings['taskDatePadding'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['genericproperties']['extendCategoryBg'] = array(
    '#type' => 'checkbox',
    '#title' => t('Extend category background'),
    '#default_value' => $settings['extendCategoryBg'],
    '#description' => t('Whether the background for the last sub-category (date range on the top of chart) will extend till the bottom of the chart.'),
    '#attributes' => ($settings['extendCategoryBg'] == 1 ? array('checked' => 'checked') : array()),
    );
  return $form;
}
function _fusioncharts_Font($settings) {
  $form['settings']['font'] = array(
    '#type' => 'fieldset',
    '#title' => t('Font properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['font']['baseFont'] = array(
    '#type' => 'select',
    '#title' => t('Font name'),
    '#default_value' => ($settings['baseFont'] ? $settings['baseFont'] : 'Arial'),
    '#options' => array("Arial" => "Arial", "Helvetica" => "Helvetica", "Times New Roman" => "Times New Roman", "Times" => "Times", "Courier New" => "Courier New", "Courier" => "Courier", "Georgia" => "Georgia", "Verdana" => "Verdana", "Geneva" => "Geneva"),
    '#description' => t('The base font of the chart; the font which lies on the canvas.'),
    );
  $form['settings']['font']['baseFontSize'] = array(
    '#type' => 'select',
    '#title' => t('Font size'),
    '#default_value' => ($settings['baseFontSize'] ? $settings['baseFontSize'] : 10),
    '#options'  =>  array(6 => 6, 7  => 7, 8 => 8, 9 => 9, 10 => 10, 11 => 11, 12 => 12, 13 => 13, 14 => 14, 15 => 15, 16 => 16, 17 => 17, 18 => 18, 19 => 19, 20 => 20, 21 => 21, 22 => 22, 23 => 23, 24 => 24),
    '#description' => t('The base font size.'),
    );
  $form['settings']['font']['baseFontColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Font color'),
    );
  $form['settings']['font']['baseFontColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The base font color.'),
    '#default_value' => ($settings['baseFontColor'] ? $settings['baseFontColor'] : '#000000'),
    '#colorpicker' => 'settings_font_baseFontColor_colorpicker',
    );
  return $form;
}
function _fusioncharts_Font_extra($settings) {
  $form['settings']['font']['outCnvBaseFont'] = array(
    '#type' => 'select',
    '#title' => t('Canvas font name'),
    '#default_value' => ($settings['outCnvBaseFont'] ? $settings['outCnvBaseFont'] : 'Arial'),
    '#options' => array("Arial" => "Arial", "Helvetica" => "Helvetica", "Times New Roman" => "Times New Roman", "Times" => "Times", "Courier New" => "Courier New", "Courier" => "Courier", "Georgia" => "Georgia", "Verdana" => "Verdana", "Geneva" => "Geneva"),
    '#description' => t('The font of the chart; the font which lies outside the canvas.'),
    );
  $form['settings']['font']['outCnvBaseFontSze'] = array(
    '#type' => 'select',
    '#title' => t('Canvas font size'),
    '#default_value' => ($settings['outCnvBaseFontSze'] ? $settings['outCnvBaseFontSze'] : 14),
    '#options'  =>  array(6 => 6, 7  => 7, 8 => 8, 9 => 9, 10 => 10, 11 => 11, 12 => 12, 13 => 13, 14 => 14, 15 => 15, 16 => 16, 17 => 17, 18 => 18, 19 => 19, 20 => 20, 21 => 21, 22 => 22, 23 => 23, 24 => 24),
    '#description' => t('The chart font size.'),
    );
  $form['settings']['font']['outCnvBaseFontColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Canvas font color'),
    );
  $form['settings']['font']['outCnvBaseFontColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The font color of the chart.'),
    '#default_value' => ($settings['outCnvBaseFontColor'] ? $settings['outCnvBaseFontColor'] : '#000000'),
    '#colorpicker' => 'settings_font_outCnvBaseFontColor_colorpicker',
    );
  return $form;
}
function _fusioncharts_NumberFormatting($settings) {
  $form['settings']['numberformating'] = array(
    '#type' => 'fieldset',
    '#title' => t('Number Formatting Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['numberformating']['numberPrefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Number prefix'),
    '#default_value' => ($settings['numberPrefix'] ? $settings['numberPrefix'] : ''),
    '#description' => t('Add prefix to all the numbers visible on the graph. For example, to represent all dollars figure on the chart, you could specify this attribute to \' $\' to show like $40000, $50000.'),
    '#size' => 5,
    );
  $form['settings']['numberformating']['numberSuffix'] = array(
    '#type' => 'textfield',
    '#title' => t('Number sufffix'),
    '#default_value' => ($settings['numberSuffix'] ? urldecode($settings['numberSuffix']) : ''), //have you encoded this yet aaron?
    '#description' => t('Add suffix to all the numbers visible on the graph. For example, to represent all figure quantified as per annum on the chart, you could specify this attribute to \' /a\' to show like 40000/a, 50000/a.'),
    '#size' => 5,
    );
  $form['settings']['numberformating']['formatNumber'] = array(
    '#type' => 'checkbox',
    '#title' => t('Format numbers'),
    '#default_value' => $settings['formatNumber'],
    '#description' => t('Whether the numbers displayed on the chart will be formatted using commas, e.g., 40,000 if ticked and 40000 if unticked'),
    '#attributes' => ($settings['formatNumber'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['numberformating']['formatNumberScale'] = array(
    '#type' => 'checkbox',
    '#title' => t('Format number scale'),
    '#default_value' => $settings['formatNumberScale'],
    '#description' => t('Whether to add K (thousands) and M (millions) to a number after truncating and rounding it - e.g., if ticked, 10434 would become 1.04K (with decimalPrecision set to 2 places). Same with numbers in millions - a M will added at the end.'),
    '#attributes' => ($settings['formatNumberScale'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['numberformating']['decimalSeparator'] = array(
    '#type' => 'textfield',
    '#title' => t('Decimal seperator'),
    '#default_value' => ($settings['decimalSeparator'] ? $settings['decimalSeparator'] : '.'), 
    '#description' => t('Specify the character to be used as the decimal separator in a number.'),
    '#size' => 5,
    );
  $form['settings']['numberformating']['thousandSeparator'] = array(
    '#type' => 'textfield',
    '#title' => t('Thousand seperator'),
    '#default_value' => ($settings['thousandSeparator'] ? $settings['thousandSeparator'] : ','), 
    '#description' => t('Specify the character to be used as the thousands separator in a number.'),
    '#size' => 5,
    );
  $form['settings']['numberformating']['decimalPrecision'] = array(
    '#type' => 'textfield',
    '#title' => t('Decimal precision'),
    '#default_value' => ($settings['decimalPrecision'] ? $settings['decimalPrecision'] : '0'), 
    '#description' => t('Number of decimal places to which all numbers on the chart would be rounded to.'),
    '#size' => 5,
    );
  return $form;
}

function _fusioncharts_NumberFormatting_extra($settings) {
  $form['settings']['numberformating']['divLineDecimalPrecision'] = array(
    '#type' => 'textfield',
    '#title' => t('Divisional line (horizontal) rounding'),
    '#default_value' => ($settings['divLineDecimalPrecision'] ? $settings['divLineDecimalPrecision'] : '0'), 
    '#description' => t('Number of decimal places to which all divisional line (horizontal) values on the chart would be rounded to.'),
    '#size' => 5,
    );
  $form['settings']['numberformating']['limitsDecimalPrecision'] = array(
    '#type' => 'textfield',
    '#title' => t('Upper and lower limits rounding'),
    '#default_value' => ($settings['limitsDecimalPrecision'] ? $settings['limitsDecimalPrecision'] : '0'), 
    '#description' => t('Number of decimal places to which upper and lower limit values on the chart would be rounded to.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_ZeroPlane($settings) {
  $form['settings']['zeroplane'] = array(
    '#type' => 'fieldset',
    '#title' => t('Zero Plane'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['zeroplane']['zeroPlaneThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Thickness of the zero line'),
    '#default_value' => ($settings['zeroPlaneThickness'] ? $settings['zeroPlaneThickness'] : ''),
    '#description' => t('Thickness (in pixels) of the line indicating the zero plane.'),
    '#size' => 5,
    );
  $form['settings']['zeroplane']['zeroPlaneColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color of the zero line'),
    );
  $form['settings']['zeroplane']['zeroPlaneColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color for the zero plane.'),
    '#default_value' => ($settings['zeroPlaneColor'] ? $settings['zeroPlaneColor'] : '#000000'),
    '#colorpicker' => 'settings_zeroplane_zeroPlaneColor_colorpicker',
    );
  $form['settings']['zeroplane']['zeroPlaneAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Transparency of the zero line'),
    '#default_value' => ($settings['zeroPlaneAlpha'] ? $settings['zeroPlaneAlpha'] : ''),
    '#description' => t('The transparency for the zero plane (0-100).'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_ZeroPlane_extra($settings) {
  $form['settings']['zeroplane']['zeroPlaneShowBorder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show border of 3D plot'),
    '#default_value' => $settings['zeroPlaneShowBorder'],
    '#description' => t('Whether the border of a 3D zero plane would be plotted or not.'),
    '#attributes' => ($settings['zeroPlaneShowBorder'] == 1 ? array('checked' => 'checked') : array()),
    );
  return $form;
}
function _fusioncharts_divisionalH($settings) {
  $form['settings']['divisionalH'] = array(
    '#type' => 'fieldset',
    '#title' => t('Divisional Lines (Horizontal)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['divisionalH']['numdivlines'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of divisional lines'),
    '#default_value' => ($settings['numdivlines'] ? $settings['numdivlines'] : ''),
    '#description' => t('The number of divisional lines to be drawn.'),
    '#size' => 5,
    );
  $form['settings']['divisionalH']['divlinecolor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('The color of grid divisional line'),
    );
  $form['settings']['divisionalH']['divlinecolor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color of grid divisional line.'),
    '#default_value' => ($settings['divlinecolor'] ? $settings['divlinecolor'] : '#000000'),
    '#colorpicker' => 'settings_divisionalH_divlinecolor_colorpicker',
    );
  $form['settings']['divisionalH']['divLineThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Thickness of the grid divisional line.'),
    '#default_value' => ($settings['divLineThickness'] ? $settings['divLineThickness'] : ''),
    '#description' => t('Thickness (in pixels) of the grid divisional line.'),
    '#size' => 5,
    );
  $form['settings']['divisionalH']['divLineAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Transparency of the grid divisional line.'),
    '#default_value' => ($settings['divLineAlpha'] ? $settings['divLineAlpha'] : ''),
    '#description' => t('Transparency of the grid divisional line (0-100).'),
    '#size' => 5,
    );
  $form['settings']['divisionalH']['showDivLineValue'] = array(
    '#type' => 'checkbox',
    '#title' => t('Textural value'),
    '#default_value' => $settings['showDivLineValue'],
    '#description' => t('Show/hide the textual value of the divisional line.'),
    '#attributes' => ($settings['showDivLineValue'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['divisionalH']['showAlternateHGridColor'] = array(
    '#type' => 'checkbox',
    '#title' => t('Alternate colored grid bands'),
    '#default_value' => $settings['showAlternateHGridColor'],
    '#description' => t('Whether to show alternate colored horizontal grid bands.'),
    '#attributes' => ($settings['showAlternateHGridColor'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['divisionalH']['alternateHGridColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color of the alternate horizontal grid bands'),
    );
  $form['settings']['divisionalH']['alternateHGridColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Color of the alternate horizontal grid bands.'),
    '#default_value' => ($settings['alternateHGridColor'] ? $settings['alternateHGridColor'] : '#000000'),
    '#colorpicker' => 'settings_divisionalH_alternateHGridColor_colorpicker',
    );
  $form['settings']['divisionalH']['alternateHGridAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Transparency of the alternate grid divisional line'),
    '#default_value' => ($settings['alternateHGridAlpha'] ? $settings['alternateHGridAlpha'] : ''),
    '#description' => t('Transparency of the alternate horizontal grid bands (0-100).'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_divisionalV($settings) {
  $form['settings']['divisionalV'] = array(
    '#type' => 'fieldset',
    '#title' => t('Divisional Lines (Vertical)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['divisionalV']['numVDivLines'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of divisional lines'),
    '#default_value' => ($settings['numVDivLines'] ? $settings['numVDivLines'] : ''),
    '#description' => t('The number of vertical divisional lines to be drawn.'),
    '#size' => 5,
    );
  $form['settings']['divisionalV']['VDivlinecolor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color of vertical grid divisional line'),
    );
  $form['settings']['divisionalV']['VDivlinecolor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Color of vertical grid divisional line.'),
    '#default_value' => ($settings['VDivlinecolor'] ? $settings['VDivlinecolor'] : '#000000'),
    '#colorpicker' => 'settings_divisionalV_VDivlinecolor_colorpicker',
    );
  $form['settings']['divisionalV']['VDivLineThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Thickness of the grid divisional line.'),
    '#default_value' => ($settings['VDivLineThickness'] ? $settings['VDivLineThickness'] : ''),
    '#description' => t('Thickness (in pixels) of the grid divisional line.'),
    '#size' => 5,
    );
  $form['settings']['divisionalV']['VDivLineAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Transparency of the grid divisional line.'),
    '#default_value' => ($settings['VDivLineAlpha'] ? $settings['VDivLineAlpha'] : ''),
    '#description' => t('Transparency of the grid divisional line (0-100).'),
    '#size' => 5,
    );
  $form['settings']['divisionalV']['showAlternateVGridColor'] = array(
    '#type' => 'checkbox',
    '#title' => t('Alternate colored grid bands'),
    '#default_value' => $settings['showAlternateVGridColor'],
    '#description' => t('Whether to show alternate colored vertical grid bands.'),
    '#attributes' => ($settings['showAlternateVGridColor'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['divisionalV']['alternateVGridColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color of the alternate vertical grid bands'),
    );
  $form['settings']['divisionalV']['alternateVGridColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Color of the alternate vertical grid bands.'),
    '#default_value' => ($settings['alternateVGridColor'] ? $settings['alternateVGridColor'] : '#000000'),
    '#colorpicker' => 'settings_divisionalV_alternateVGridColor_colorpicker',
    );
  $form['settings']['divisionalV']['alternateVGridAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Transparency of the alternate grid divisional line.'),
    '#default_value' => ($settings['alternateVGridAlpha'] ? $settings['alternateVGridAlpha'] : ''),
    '#description' => t('Transparency of the alternate horizontal grid bands (9-100).'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_HoverCaption($settings) {
  $form['settings']['HoverCaption'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hover Caption Properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['HoverCaption']['showhovercap'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hover caption'),
    '#default_value' => $settings['showhovercap'],
    '#description' => t('Whether to show/hide hover caption box.'),
    '#attributes' => ($settings['showhovercap'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['HoverCaption']['hoverCapBgColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Background color of the hover caption box'),
    );
  $form['settings']['HoverCaption']['hoverCapBgColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Background color of the hover caption box.'),
    '#default_value' => ($settings['hoverCapBgColor'] ? $settings['hoverCapBgColor'] : '#ffffff'),
    '#colorpicker' => 'settings_HoverCaption_hoverCapBgColor_colorpicker',
    );
  $form['settings']['HoverCaption']['hoverCapBorderColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Border color of the hover caption box'),
    );
  $form['settings']['HoverCaption']['hoverCapBorderColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Border color of the hover caption box.'),
    '#default_value' => ($settings['hoverCapBorderColor'] ? $settings['hoverCapBorderColor'] : '#000000'),
    '#colorpicker' => 'settings_HoverCaption_hoverCapBorderColor_colorpicker',
    );
  $form['settings']['HoverCaption']['hoverCapSepChar'] = array(
    '#type' => 'textfield',
    '#title' => t('Character seperator'),
    '#default_value' => ($settings['hoverCapSepChar'] ? $settings['hoverCapSepChar'] : ''),
    '#description' => t('The character that separates the name and value displayed in the hover caption box.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_ChartMargins($settings) {
  $form['settings']['ChartMargins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chart Margins'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['ChartMargins']['chartLeftMargin'] = array(
    '#type' => 'textfield',
    '#title' => t('Left space'),
    '#default_value' => ($settings['chartLeftMargin'] ? $settings['chartLeftMargin'] : ''),
    '#description' => t('Space to be left unplotted on the left side of the chart.'),
    '#size' => 5,
    );
  $form['settings']['ChartMargins']['chartRightMargin'] = array(
    '#type' => 'textfield',
    '#title' => t('Right space'),
    '#default_value' => ($settings['chartRightMargin'] ? $settings['chartRightMargin'] : ''),
    '#description' => t('Space to be left unplotted on the right side of the chart.'),
    '#size' => 5,
    );
  $form['settings']['ChartMargins']['chartTopMargin'] = array(
    '#type' => 'textfield',
    '#title' => t('Top space'),
    '#default_value' => ($settings['chartTopMargin'] ? $settings['chartTopMargin'] : ''),
    '#description' => t('Space to be left unplotted on the top of the chart.'),
    '#size' => 5,
    );
  $form['settings']['ChartMargins']['chartBottomMargin'] = array(
    '#type' => 'textfield',
    '#title' => t('Bottom space'),
    '#default_value' => ($settings['chartBottomMargin'] ? $settings['chartBottomMargin'] : ''),
    '#description' => t('Space to be left unplotted on the bottom of the chart.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_PieProperties($settings) {
  $form['settings']['PieProperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pie properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['PieProperties']['pieRadius'] = array(
    '#type' => 'textfield',
    '#title' => t('Pie radius'),
    '#default_value' => ($settings['pieRadius'] ? $settings['pieRadius'] : ''),
    '#description' => t('Fusion Charts automatically calculates the best fit pie radius for the chart. However, if you want to enforce one of your own radius values, you can set it here.'),
    '#size' => 5,
    );
  $form['settings']['PieProperties']['pieBorderThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Border thickness'),
    '#default_value' => ($settings['pieBorderThickness'] ? $settings['pieBorderThicknessYScale'] : ''),
    '#description' => t('Each pie on the chart has a border, whose thickness you can specify here.'),
    '#size' => 5,
    );
  $form['settings']['PieProperties']['pieBorderAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Pie border transparency'),
    '#default_value' => ($settings['pieBorderAlpha'] ? $settings['pieBorderAlpha'] : ''),
    '#description' => t('The border transparency for all the pie borders.'),
    '#size' => 5,
    );
  $form['settings']['PieProperties']['pieFillAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Pie filling transparency'),
    '#default_value' => ($settings['pieFillAlpha'] ? $settings['pieFillAlpha'] : ''),
    '#description' => t('The transparency of the pie slices. '),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_PieProperties_extra($settings) {
  $form['settings']['PieProperties']['pieSliceDepth'] = array(
    '#type' => 'textfield',
    '#title' => t('Pie slice depth'),
    '#default_value' => ($settings['pieSliceDepth'] ? $settings['pieSliceDepth'] : ''),
    '#description' => t('The 3D height of the chart (in pixels).'),
    '#size' => 5,
    );
  $form['settings']['PieProperties']['pieYScale'] = array(
    '#type' => 'textfield',
    '#title' => t('Pie Y scale'),
    '#default_value' => ($settings['pieYScale'] ? $settings['pieYScale'] : ''),
    '#description' => t('The skewness (vertical slant) of the pie chart (30-100).'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_PieProperties2($settings) {
  $form['settings']['PieProperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pie properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['PieProperties']['pieRadius'] = array(
    '#type' => 'textfield',
    '#title' => t('Pie radius'),
    '#default_value' => ($settings['pieRadius'] ? $settings['pieRadius'] : ''),
    '#description' => t('Fusion Charts automatically calculates the best fit pie radius for the chart. However, if you want to enforce one of your own radius values, you can set it here.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_PieShadowProperties($settings) {
  $form['settings']['PieShadowProperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pie shadow properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['PieShadowProperties']['showShadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show shadow'),
    '#default_value' => $settings['showShadow'],
    '#attributes' => ($settings['showShadow'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['PieShadowProperties']['shadowColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Shadow color'),
    );
  $form['settings']['PieShadowProperties']['shadowColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color of the shadow.'),
    '#default_value' => ($settings['shadowColor'] ? $settings['shadowColor'] : '#cccccc'),
    '#colorpicker' => 'settings_PieShadowProperties_shadowColor_colorpicker',
    );
  $form['settings']['PieShadowProperties']['shadowAlpha '] = array(
    '#type' => 'textfield',
    '#title' => t('Shadow transparency'),
    '#default_value' => ($settings['shadowAlpha '] ? $settings['shadowAlpha '] : ''),
    '#description' => t('The transparency of the shadow.'),
    '#size' => 5,
    );
  $form['settings']['PieShadowProperties']['shadowXShift'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadow X shift'),
    '#default_value' => ($settings['shadowXShift'] ? $settings['shadowXShift'] : ''),
    '#description' => t('The X shift of the shadow pie from the actual pie. That is, if you want to show the shadow 3 pixel right from the actual pie, set this to 3. Similarly, if you want the shadow to appear on the left of the actual pie, set it to -3.'),
    '#size' => 5,
    );
  $form['settings']['PieShadowProperties']['shadowYShift'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadow Y shift'),
    '#default_value' => ($settings['shadowYShift'] ? $settings['shadowYShift'] : ''),
    '#description' => t('The Y shift of the shadow pie from the actual pie. That is, if you want to show the shadow 3 pixel below the actual pie, set this to 3. Similarly, if you want the shadow to appear above the actual pie, set it to -3.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_PieShadowProperties2($settings) {
  $form['settings']['PieShadowProperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pie shadow properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['PieShadowProperties']['showShadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show shadow'),
    '#default_value' => $settings['showShadow'],
    '#attributes' => ($settings['showShadow'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['PieShadowProperties']['shadowColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Shadow color'),
    );
  $form['settings']['PieShadowProperties']['shadowColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color of the shadow color.'),
    '#default_value' => ($settings['shadowColor'] ? $settings['shadowColor'] : '#cccccc'),
    '#colorpicker' => 'settings_PieShadowProperties_shadowColor_colorpicker',
    );
  return $form;
}
function _fusioncharts_NameValuedisplaydistance($settings) {
  $form['settings']['NameValuedisplaydistance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name/Value display distance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['NameValuedisplaydistance']['nameTBDistance'] = array(
    '#type' => 'textfield',
    '#title' => t('Name/value distance from pie edge'),
    '#default_value' => ($settings['nameTBDistance'] ? $settings['nameTBDistance'] : ''),
    '#description' => t('The distance of the name/value text boxes from the pie edge.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_NameValuedisplaydistance_extra($settings) {
  $form['settings']['NameValuedisplaydistance']['slicingDistance'] = array(
    '#type' => 'textfield',
    '#title' => t('Slicing distance'),
    '#default_value' => ($settings['slicingDistance'] ? $settings['slicingDistance'] : ''),
    '#description' => t('If you\'ve opted to slice a particular pie, using this attribute you can control the distance between the sliced pie and the center of other pies.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_LineProperties($settings) {
  $form['settings']['LineProperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Line properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['LineProperties']['lineColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Line color'),
    );
  $form['settings']['LineProperties']['lineColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color of the shadow.'),
    '#default_value' => ($settings['lineColor'] ? $settings['lineColor'] : '#ff0000'),
    '#colorpicker' => 'settings_LineProperties_lineColor_colorpicker',
    );
  $form['settings']['LineProperties']['lineThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Line thickness'),
    '#default_value' => ($settings['lineThickness'] ? $settings['lineThickness'] : ''),
    '#description' => t('Thickness of the line (in pixels).'),
    '#size' => 5,
    );
  $form['settings']['LineProperties']['lineAlpha '] = array(
    '#type' => 'textfield',
    '#title' => t('Line transparency'),
    '#default_value' => ($settings['lineAlpha '] ? $settings['lineAlpha '] : ''),
    '#description' => t('The transparency of the line.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_LineShadowProperties($settings) {
  $form['settings']['LineShadowProperties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Line shadow properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['LineShadowProperties']['showShadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show shadow'),
    '#default_value' => $settings['showShadow'],
    '#attributes' => ($settings['showShadow'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['LineShadowProperties']['shadowColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Shadow color'),
    );
  $form['settings']['LineShadowProperties']['shadowColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color of the shadow.'),
    '#default_value' => ($settings['shadowColor'] ? $settings['shadowColor'] : '#cccccc'),
    '#colorpicker' => 'settings_LineShadowProperties_shadowColor_colorpicker',
    );
  $form['settings']['LineShadowProperties']['shadowAlpha '] = array(
    '#type' => 'textfield',
    '#title' => t('Shadow transparency'),
    '#default_value' => ($settings['shadowAlpha '] ? $settings['shadowAlpha '] : ''),
    '#description' => t('The transparency of the shadow line.'),
    '#size' => 5,
    );
  $form['settings']['LineShadowProperties']['shadowXShift'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadow X shift'),
    '#default_value' => ($settings['shadowXShift'] ? $settings['shadowXShift'] : ''),
    '#description' => t('The X shift of the shadow line from the chart line. That is, if you want to show the shadow 3 pixel right from the actual line, set this to 3. Similarly, if you want the shadow to appear on the left of the actual line, set it to -3.'),
    '#size' => 5,
    );
  $form['settings']['LineShadowProperties']['shadowYShift'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadow Y shift'),
    '#default_value' => ($settings['shadowYShift'] ? $settings['shadowYShift'] : ''),
    '#description' => t('This attribute helps you set the Y shift of the shadow line from the chart line. That is, if you want to show the shadow 3 pixel below the actual line, set this to 3. Similarly, if you want the shadow to appear above the actual line, set it to -3.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_Anchor($settings) {
  $form['settings']['Anchor'] = array(
    '#type' => 'fieldset',
    '#title' => t('Anchor properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['Anchor']['showAnchors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show anchors'),
    '#default_value' => $settings['showAnchors'],
    '#description' => t('Whether the anchors would be shown on the chart or not. If the anchors are not shown, then the hover caption and link functions won\'t work.'),
    '#attributes' => ($settings['showAnchors'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['Anchor']['anchorSides'] = array(
    '#type' => 'textfield',
    '#title' => t('Anchor sides'),
    '#default_value' => ($settings['anchorSides'] ? $settings['anchorSides'] : ''),
    '#description' => t('Numeric Value greater than 3: This sets the number of sides the anchor will have. For e.g., an anchor with 3 sides would represent a triangle, with 4 it would be a square and so on.'),
    '#size' => 5,
    );
  $form['settings']['Anchor']['anchorRadius'] = array(
    '#type' => 'textfield',
    '#title' => t('Anchor raduis'),
    '#default_value' => ($settings['anchorRadius'] ? $settings['anchorRadius'] : ''),
    '#description' => t('The radius (in pixels) of the anchor. Greater the radius, the bigger the anchor size.'),
    '#size' => 5,
    );
  $form['settings']['Anchor']['anchorBorderColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Anchor border color'),
    );
  $form['settings']['Anchor']['anchorBorderColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Border color of the anchor.'),
    '#default_value' => ($settings['anchorBorderColor'] ? $settings['anchorBorderColor'] : '#555555'),
    '#colorpicker' => 'settings_Anchor_anchorBorderColor_colorpicker',
    );
  $form['settings']['Anchor']['anchorBorderThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Anchor border thickness'),
    '#default_value' => ($settings['anchorBorderThickness'] ? $settings['anchorBorderThickness'] : ''),
    '#description' => t('Thickness of the anchor border (in pixels).'),
    '#size' => 5,
    );
  $form['settings']['Anchor']['anchorAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Anchor transparency'),
    '#default_value' => ($settings['anchorAlpha'] ? $settings['anchorAlpha'] : ''),
    '#description' => t('The tranparency of the entire anchor (including the border). This is particularly useful, when you do not want the anchors to be visible on the chart, but you want the hover caption and link functionality. In that case, you can untick this.'),
    '#size' => 5,
    );
  $form['settings']['Anchor']['anchorBgColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Anchor background color'),
    );
  $form['settings']['Anchor']['anchorBgColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Background color of the anchor.'),
    '#default_value' => ($settings['anchorBgColor'] ? $settings['anchorBgColor'] : '#ff0000'),
    '#colorpicker' => 'settings_Anchor_anchorBgColor_colorpicker',
    );
  $form['settings']['Anchor']['anchorBgAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Anchor background transparency'),
    '#default_value' => ($settings['anchorBgAlpha'] ? $settings['anchorBgAlpha'] : ''),
    '#description' => t('Transparency of the anchor background (0-100).'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_Area($settings) {
  $form['settings']['Area'] = array(
    '#type' => 'fieldset',
    '#title' => t('Area properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['Area']['showAreaBorder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show borders over the area'),
    '#default_value' => $settings['showAreaBorder'],
    '#description' => t('Whether the border over the area would be shown or not.'),
    '#attributes' => ($settings['showAreaBorder'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['Area']['areaBorderThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Area border thickness'),
    '#default_value' => ($settings['areaBorderThickness'] ? $settings['areaBorderThickness'] : ''),
    '#description' => t('If the area border is to be shown, this sets the thickness (in pixels) of the area border.'),
    '#size' => 5,
    );
  $form['settings']['Area']['areaBorderColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Area border color'),
    );
  $form['settings']['Area']['areaBorderColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Area border color'),
    '#default_value' => ($settings['areaBorderColor'] ? $settings['areaBorderColor'] : '#555555'),
    '#colorpicker' => 'settings_Area_areaBorderColor_colorpicker',
    );
  $form['settings']['Area']['areaAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Area transparency'),
    '#default_value' => ($settings['areaAlpha'] ? $settings['areaAlpha'] : ''),
    '#description' => t('Transparency of the area fill.'),
    '#size' => 5,
    );
  $form['settings']['Area']['areaBgColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Area background color'),
    );
  $form['settings']['Area']['areaBgColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('If you want the entire area chart to be filled with one color, set that color here.'),
    '#default_value' => ($settings['areaBgColor'] ? $settings['areaBgColor'] : '#ffffff'),
    '#colorpicker' => 'settings_Area_areaBgColor_colorpicker',
    );
  return $form;
}
function _fusioncharts_Candle($settings) {
  $form['settings']['Candle'] = array(
    '#type' => 'fieldset',
    '#title' => t('Candle properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['Candle']['candleWidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Candle width'),
    '#default_value' => ($settings['candleWidth'] ? $settings['candleWidth'] : ''),
    '#description' => t('If you explicitly wish to define the width of each candle in the chart, you can use set it here. However, this attribute is optional in the sense that Fusion Charts would automatically calculate the best fit value for the candle width.'),
    '#size' => 5,
    );
  $form['settings']['Candle']['bearBorderColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Fill Color for a bear candle'),
    );
  $form['settings']['Candle']['bearBorderColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Fill Color for a bear candle.'),
    '#default_value' => ($settings['bearBorderColor'] ? $settings['bearBorderColor'] : '#555555'),
    '#colorpicker' => 'settings_Candle_bearBorderColor_colorpicker',
    );
  $form['settings']['Candle']['bearFillColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Area background color'),
    );
  $form['settings']['Candle']['bearFillColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('If you want the entire area chart to be filled with one color, set that color for this attribute.'),
    '#default_value' => ($settings['bearFillColor'] ? $settings['bearFillColor'] : '#ff0000'),
    '#colorpicker' => 'settings_Candle_bearFillColor_colorpicker',
    );
  $form['settings']['Candle']['bullBorderColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Border Color for a bull candle'),
    );
  $form['settings']['Candle']['bullBorderColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Border Color for a bull candle.'),
    '#default_value' => ($settings['bullBorderColor'] ? $settings['bullBorderColor'] : '#ffffff'),
    '#colorpicker' => 'settings_Candle_bullBorderColor_colorpicker',
    );
  $form['settings']['Candle']['bullFillColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Fill Color for a bull candle'),
    );
  $form['settings']['Candle']['bullFillColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('Fill Color for a bull candle.'),
    '#default_value' => ($settings['bullFillColor'] ? $settings['bullFillColor'] : '#ff0000'),
    '#colorpicker' => 'settings_Candle_bullFillColor_colorpicker',
    );
  return $form;
}
function _fusioncharts_GanttGeneral($settings) {
  $form['settings']['GanttGeneral'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gantt General Properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['GanttGeneral']['ganttWidthPercent'] = array(
    '#type' => 'textfield',
    '#title' => t('Gantt Width'),
    '#default_value' => ($settings['ganttWidthPercent'] ? $settings['ganttWidthPercent'] : ''),
    '#description' => t('The Gantt chart consists of two parts - the Gantt chart and the data table (including process names). This attribute lets you set the width of the gantt part, in percentage, with respect to the whole chart (0-100).'),
    '#size' => 5,
    );
  $form['settings']['GanttGeneral']['ganttLineColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Line color'),
    );
  $form['settings']['GanttGeneral']['ganttLineColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('The color of the lines running through the Gantt chart as background.'),
    '#default_value' => ($settings['ganttLineColor'] ? $settings['ganttLineColor'] : '#000000'),
    '#colorpicker' => 'settings_GanttGeneral_ganttLineColor_colorpicker',
    );
  $form['settings']['GanttGeneral']['ganttLineThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Line thickness'),
    '#default_value' => ($settings['ganttLineThickness'] ? $settings['ganttLineThickness'] : ''),
    '#description' => t('The thickness of the lines running through the Gantt chart as background.'),
    '#size' => 5,
    );
  $form['settings']['GanttGeneral']['ganttLineAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Line transparency'),
    '#default_value' => ($settings['ganttLineAlpha'] ? $settings['ganttLineAlpha'] : ''),
    '#description' => t('The transparency of the lines running through the Gantt chart as background.'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_DataTable($settings) {
  $form['settings']['DataTable'] = array(
    '#type' => 'fieldset',
    '#title' => t('Data Table Properties'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['settings']['DataTable']['gridBorderColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Grid border color'),
    '#description' => t('The color of the border of data table (which shows the process names and additional information).'),
    );
  $form['settings']['DataTable']['gridBorderColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#title' => t('Grid border color'),
    '#default_value' => ($settings['gridBorderColor'] ? $settings['gridBorderColor'] : '#555555'),
    '#colorpicker' => 'settings_DataTable_gridBorderColor_colorpicker',
    );
  $form['settings']['DataTable']['gridBorderAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Grid border transparency'),
    '#default_value' => ($settings['gridBorderAlpha'] ? $settings['gridBorderAlpha'] : ''),
    '#description' => t('This attribute sets the transparency of the border of data table (which shows the process names and additional information) (0-100).'),
    '#size' => 5,
    );
  $form['settings']['DataTable']['gridResizeBarColor_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Grid resize bar color'),
    );
  $form['settings']['DataTable']['gridResizeBarColor'] = array(
    '#type' => 'colorpicker_textfield',
    '#description' => t('If you show two columns of information in the data table, you\'ll find that the data table is draggable i.e., you can resize each of the columns using a resize bar. This sets the color of that resize bar.'),
    '#default_value' => ($settings['gridResizeBarColor'] ? $settings['gridResizeBarColor'] : '#cccccc'),
    '#colorpicker' => 'settings_DataTable_gridResizeBarColor_colorpicker',
    );
  $form['settings']['DataTable']['gridResizeBarThickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Resize bar thickness'),
    '#default_value' => ($settings['gridResizeBarThickness'] ? $settings['gridResizeBarThickness'] : ''),
    '#description' => t('Set the thickness of the resize bar (pixels).'),
    '#size' => 5,
    );
  $form['settings']['DataTable']['gridResizeBarAlpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Resize bar transparency'),
    '#default_value' => ($settings['gridResizeBarAlpha'] ? $settings['gridResizeBarAlpha'] : ''),
    '#description' => t('The transparency of the resize bar (0-100).'),
    '#size' => 5,
    );
  return $form;
}
function _fusioncharts_Colors($attributes) {
  $form['attributes']['Color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Colors'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('This is where you set the colors of the bars/pie slices'),
    );
  $form['attributes']['Color']['color1_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 1'),
    );
  $form['attributes']['Color']['color1'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color1'] ? $attributes['color1'] : '#AFD8F8'),
    '#colorpicker' => 'attributes_Color_color1_colorpicker',
    );
  $form['attributes']['Color']['color2_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 2'),
     );
  $form['attributes']['Color']['color2'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color2'] ? $attributes['color2'] : '#F6BD0F'),
    '#colorpicker' => 'attributes_Color_color2_colorpicker',
    );
  $form['attributes']['Color']['color3_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 3'),
    );
  $form['attributes']['Color']['color3'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color3'] ? $attributes['color3'] : '#8BBA00'),
    '#colorpicker' => 'attributes_Color_color3_colorpicker',
    );
  $form['attributes']['Color']['color4_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 4'),
    );
  $form['attributes']['Color']['color4'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color4'] ? $attributes['color4'] : '#FF8E46'),
    '#colorpicker' => 'attributes_Color_color4_colorpicker',
    );
  $form['attributes']['Color']['color5_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 5'),
    );
  $form['attributes']['Color']['color5'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color5'] ? $attributes['color5'] : '#008E8E'),
    '#colorpicker' => 'attributes_Color_color5_colorpicker',
    );
  $form['attributes']['Color']['color6_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 6'),
    );
  $form['attributes']['Color']['color6'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color6'] ? $attributes['color6'] : '#D64646'),
    '#colorpicker' => 'attributes_Color_color6_colorpicker',
    );
  $form['attributes']['Color']['color7_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 7'),
    );
  $form['attributes']['Color']['color7'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color7'] ? $attributes['color7'] : '#8E468E'),
    '#colorpicker' => 'attributes_Color_color7_colorpicker',
    );
  $form['attributes']['Color']['color8_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 8'),
    );
  $form['attributes']['Color']['color8'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color8'] ? $attributes['color8'] : '#588526'),
    '#colorpicker' => 'attributes_Color_color8_colorpicker',
    );
  $form['attributes']['Color']['color9_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 9'),
    );
  $form['attributes']['Color']['color9'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color9'] ? $attributes['color9'] : '#B3AA00'),
    '#colorpicker' => 'attributes_Color_color9_colorpicker',
    );
  $form['attributes']['Color']['color10_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 10'),
    );
  $form['attributes']['Color']['color10'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color10'] ? $attributes['color10'] : '#008ED6'),
    '#colorpicker' => 'attributes_Color_color10_colorpicker',
    );
  $form['attributes']['Color']['color11_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 11'),
    );
  $form['attributes']['Color']['color11'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color11'] ? $attributes['color11'] : '#9D080D'),
    '#colorpicker' => 'attributes_Color_color11_colorpicker',
    );
  $form['attributes']['Color']['color12_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Color 12'),
    );
  $form['attributes']['Color']['color12'] = array(
    '#type' => 'colorpicker_textfield',
    '#default_value' => ($attributes['color12'] ? $attributes['color12'] : '#A186BE'),
    '#colorpicker' => 'attributes_Color_color12_colorpicker',
    );
    return $form;
}
function _fusioncharts_Trendline($attributes) {
  $form['attributes']['Trendline'] = array(
    '#type' => 'fieldset',
    '#title' => t('Trendline'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['attributes']['Trendline']['StartValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Start Value'),
    '#default_value' => ($attributes['StartValue'] ? $attributes['StartValue'] : ''),
    '#description' => t('The Y value of the line (starting point)'),
    '#size' => 5,
    );      
  $form['attributes']['Trendline']['EndValue'] = array(
    '#type' => 'textfield',
    '#title' => t('End Value'),
    '#default_value' => ($attributes['EndValue'] ? $attributes['EndValue'] : ''),
    '#description' => t('The Y value of the line (end point)'),
    '#size' => 5,
    ); 
  $form['settings']['Area']['IsTrendZone'] = array(
    '#type' => 'checkbox',
    '#title' => t('Trendzone'),
    '#default_value' => $settings['IsTrendZone'],
    '#description' => t('Whenther the Start Value and End Value define a line (uncheked) or an area (checked)'),
    '#attributes' => ($settings['IsTrendZone'] == 1 ? array('checked' => 'checked') : array()),
    );
  $form['settings']['Area']['ShowOnTop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show trendline on top or under the bars.'),
    '#default_value' => $settings['ShowOnTop'],
    '#description' => t('Display the line on top of the bars (checked) or behind the bars (unchecked)'),
    '#attributes' => ($settings['ShowOnTop'] == 1 ? array('checked' => 'checked') : array()),
    );
    $form['attributes']['Trendline']['DisplayValue'] = array(
    '#type' => 'textfield',
    '#title' => t('Display text'),
    '#default_value' => ($attributes['displayvalue'] ? $attributes['displayvalue'] : ''),
    '#description' => t('The text to display beside the line.'),
    '#size' => 5,
    );    
  $form['attributes']['Trendline']['Color_colorpicker'] = array(
    '#type' => 'colorpicker',
    '#title' => t('Line color'),
    '#description' => t('The color of the trendline.'),
    );
  $form['attributes']['Trendline']['Color'] = array(
    '#type' => 'colorpicker_textfield',
    '#title' => t('Line color'),
    '#default_value' => ($attributes['Color'] ? $attributes['Color'] : '#555555'),
    '#colorpicker' => 'attributes_Trendline_Color_colorpicker',
    );
  $form['attributes']['Trendline']['Thickness'] = array(
    '#type' => 'textfield',
    '#title' => t('Line thickness'),
    '#default_value' => ($attributes['Thickness'] ? $attributes['Thickness'] : ''),
    '#description' => t('Set the thickness of the line (pixels).'),
    '#size' => 5,
    );
  $form['attributes']['Trendline']['Alpha'] = array(
    '#type' => 'textfield',
    '#title' => t('Transparency'),
    '#default_value' => ($attributes['Alpha'] ? $attributes['Alpha'] : ''),
    '#description' => t('The transparency of the trendline (0-100).'),
    '#size' => 5,
    );
  return $form;
}
