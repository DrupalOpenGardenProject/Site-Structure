<?php
/*
 * Sparkline PHP Graphing Library
 * Copyright 2004 James Byers <jbyers@gmail.com>
 * http://sparkline.org
 *
 * Dual-licensed under the BSD (LICENSE-BSD.txt) and GPL (LICENSE-GPL.txt)
 * licenses.
 *
 * $Id: primitives.php,v 1.1.2.2 2008/09/05 22:23:45 chris Exp $
 *
 * primitives doesn't draw a sparkline, only exercises the drawing primitives
 *
 */

require_once('../lib/Sparkline.php');

$sparkline = new Sparkline();
$sparkline->SetDebugLevel(DEBUG_NONE);
//$sparkline->SetDebugLevel(DEBUG_ERROR | DEBUG_WARNING | DEBUG_STATS | DEBUG_CALLS, '../log.txt');

// with any Sparkline subclass, Render would be called instead of Init
//
$sparkline->Init(100, 20);

$sparkline->DrawFill(9, 9, 'white');
$sparkline->DrawRectangleFilled(1, 9, 98, 18, 'grey');
$sparkline->DrawLine(0, 0, 19, 19, 'red');
$sparkline->DrawCircleFilled(49, 9, 10, 'black');
$sparkline->DrawPoint(96, 17, 'black');
$sparkline->DrawRectangle(0, 0, 99, 19, 'blue');
$sparkline->DrawText('test1', 0,   0, 'red',   1);
$sparkline->DrawText('test2', 25,  0, 'olive', 2);
$sparkline->DrawText('test3', 50, 0, 'blue',   3);

$sparkline->Output();

?>
