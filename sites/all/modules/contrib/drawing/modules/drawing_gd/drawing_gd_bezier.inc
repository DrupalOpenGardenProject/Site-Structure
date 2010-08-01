<?php
// $Id: drawing_gd_bezier.inc,v 1.1.2.1 2009/05/09 05:56:28 danielb Exp $

/**
 * @file
 * The bezier class.  Takes four points and draws a bezier curve.
 * Based on bezier.class.php by Reza Salehi, zaalion@yahoo.com.
 */

class bezier {
  function bezier($x0, $y0, $x1, $y1, $x2, $y2, $x3, $y3) {
    $this->dimx=400;
    $this->dimy=400;
    $this->br=0;
    $this->bg=0;
    $this->bb=0;
    $this->ar=255;
    $this->ag=255;
    $this->ab=255;
    $this->hasgrid=0;
    $this->t_start=0;
    $this->t_end=1;
    $this->render=0;
    $this->step=.01;
    $this->x0=$x0;
    $this->y0=$y0;
    $this->x1=$x1;
    $this->y1=$y1;
    $this->x2=$x2;
    $this->y2=$y2;
    $this->x3=$x3;
    $this->y3=$y3; 
    
    $this->cx=3*($x1-$x0);
    $this->bx=3*($x2-$x1)-$this->cx;
    $this->ax=$x3-$x0-$this->cx-$this->bx;
    
    $this->cy=3*($y1-$y0);
    $this->by=3*($y2-$y1)-$this->cy;
    $this->ay=$y3-$y0-$this->cy-$this->by;

    $this->function_x='('.$this->ax.')*$t*$t*$t+('.$this->bx.')*$t*$t+('.$this->cx.')*$t+'.$this->x0;
    $this->function_y='('.$this->ay.')*$t*$t*$t+('.$this->by.')*$t*$t+('.$this->cy.')*$t+'.$this->y0;
    $this->function_z=2;
    
  }
      
  //---- some validations.
  function zscale() {
    return(1);
  }
  function yscale() {
    return(1);
  }
  function xscale() {
    return(1);
  }

  function draw() {
    header("Content-type: image/jpeg");
    $image=imagecreate($this->dimx,$this->dimy+20);
    $col=imagecolorallocate($image,$this->br,$this->bg,$this->bb);
    $col1=imagecolorallocate($image,$this->ar,$this->ag,$this->ab);
    $col2=imagecolorallocate($image, 250, 250, 100);
    $col3=imagecolorallocate($image, 50, 50, 50);
    $grcol=imagecolorallocate($image,8,100,8);
            
    imageline($image, $this->dimx/2, 0, $this->dimx/2, $this->dimy, $col3);
    imageline($image, 0, $this->dimy/2, $this->dimx, $this->dimy/2, $col3);

    imageline($image, $this->x0+$this->dimx/2, -$this->y0+$this->dimy/2, $this->x1+$this->dimx/2, -$this->y1+$this->dimy/2, $col2);
    imageline($image, $this->x2+$this->dimx/2, -$this->y2+$this->dimy/2, $this->x3+$this->dimx/2, -$this->y3+$this->dimy/2, $col2);

    imagestring ($image, 2, $this->x0+$this->dimx/2, -$this->y0+$this->dimy/2, 'A', $col1);
    imagestring ($image, 2, $this->x1+$this->dimx/2, -$this->y1+$this->dimy/2, 'B', $col1);
    imagestring ($image, 2, $this->x2+$this->dimx/2, -$this->y2+$this->dimy/2, 'C', $col1);
    imagestring ($image, 2, $this->x3+$this->dimx/2, -$this->y3+$this->dimy/2, 'D', $col1);

    $j = 0;
    $colx = $col1;
    for ($t = $this->t_start; $t < $this->t_end; $t += $this->step) {
      eval('$this->x_points[$j]='.$this->xscale().'*'.$this->function_x.';');
      eval('$this->y_points[$j]='.$this->yscale().'*'.$this->function_y.';');
      eval('$this->z_points[$j]='.$this->zscale().'*'.$this->function_z.';');
      imagearc($image, $this->x_points[$j]+$this->dimx/2, ($this->y_points[$j]*(-1))+$this->dimy/2, $this->z_points[$j], $this->z_points[$j], 0, 360, $colx);
      $j++;    
    }

    imagefilledrectangle ($image, 5, $this->dimy-30, $this->dimx/2, $this->dimy+10, $col);

    imagestring ($image, 2, 10, $this->dimy-40, 'start point (A) = ('.$this->x0.','.$this->y0.')', $col1);
    imagestring ($image, 2, 10, $this->dimy-28, 'end point (D) = ('.$this->x3.','.$this->y3.')', $col1);
    imagestring ($image, 2, 10, $this->dimy-15, 'control 1 (B) = ('.$this->x1.','.$this->y1.')', $col1);
    imagestring ($image, 2, 10, $this->dimy-3 , 'control 2 (C) = ('.$this->x2.','.$this->y2.')', $col1);
    imagejpeg($image,"",100);
  }
}
   