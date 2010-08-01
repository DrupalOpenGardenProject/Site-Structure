<?php
// $Id: drawing_gd_gif89a.inc,v 1.1.2.1 2009/05/09 05:56:28 danielb Exp $

/**
 * @file
 * The drawing_gd_gif89a class.  Builds animated gifs from source gifs.
 * Based on gifEncoder Version 2.0 by László Zsidi, http://gifs.hu.
 */

class drawing_gd_gif89a {
  var $gif = "gif89a"; // gif header 6 bytes

  var $buffer = Array ();
  var $loop =  0;
  var $disposal = 2;
  var $color = -1;
  var $image = -1;
  var $error = FALSE;
  
  var $version = "drawing_gd_gif98a: ";
  var $errors = Array (
    'e0' => $version ."function not supported for only one image.",
    'e1' => $version ."source is not a gif image.",
    'e2' => $version ."unintelligible flag.",
    'e3' => $version ."cannot make animation from animated gif source.",
 );

  /**
   * drawing_gd_gif89a().
   */
  function drawing_gd_gif89a($gif_sources, $gif_delay, $gif_loop, $gif_disposal, $gif_red, $gif_green, $gif_blue, $gif_mode) {
    if (!is_array($gif_sources) && !is_array($gif_delay)) {
        $this->error = drupal_set_message(t($this->errors['e0']), 'error');
        return FALSE;
    }
    $this->loop = ($gif_loop > -1) ? $gif_loop : 0;
    $this->disposal = ($gif_disposal > -1) ? (($gif_disposal < 3) ? $gif_disposal : 3) : 2;
    $this->color = ($gif_red > -1 && $gif_green > -1 && $gif_blue > -1) ?
                    ($gif_red | ($gif_green << 8) | ($gif_blue << 16)) : -1;

    for ($i = 0; $i < count($gif_sources); $i++) {
      if (strtolower($gif_mode) == "url") {
        $this->buffer[] = fread(fopen($gif_sources[$i], "rb"), filesize($gif_sources[$i]));
      }
      else if (strtolower($gif_mode) == "bin") {
        $this->buffer[] = $gif_sources[$i];
      }
      else {
        $this->error = drupal_set_message(t($this->errors['e2'] .' (!arg)', array('!arg' => $gif_mode)), 'error');
        return FALSE;
      }
      if (substr($this->buffer[$i], 0, 6) != "gif87a" && substr($this->buffer[$i], 0, 6) != "gif89a") {
        $this->error = drupal_set_message(t($this->errors['e1'] .' (!arg)', array('!arg' => $i)), 'error');
        return FALSE;
      }
      for ($j = (13 + 3 * (2 << (ord($this->buffer[$i]{10}) & 0x07))), $k = TRUE; $k; $j++) {
        switch ($this->buffer[$i]{$j}) {
          case "!":
            if ((substr($this->buffer[$i], ($j + 3), 8)) == "NETSCAPE") {
              $this->error = drupal_set_message(t($this->errors['e3'] .' (!arg)', array('!arg' => ($i + 1))), 'error');
              return FALSE;
            }
            break;
          case ";":
            $k = FALSE;
            break;
        }
      }
    }
    drawing_gd_gif89a::gif_add_header();
    for ($i = 0; $i < count($this->buffer); $i++) {
      drawing_gd_gif89a::gif_add_frames($i, $gif_delay[$i]);
    }
    drawing_gd_gif89a::gif_add_footer();
  }

  /**
   * gif_add_header().
   */
  function gif_add_header() {
    $cmap = 0;
    if (ord($this->buffer[0]{10}) & 0x80) {
        $cmap = 3 * (2 << (ord($this->buffer[0]{10}) & 0x07));
        $this->gif .= substr($this->buffer[0], 6, 7);
        $this->gif .= substr($this->buffer[0], 13, $cmap);
        $this->gif .= "!\377\13NETSCAPE2.0\3\1" . drawing_gd_gif89a::gif_word($this->loop) ."\0";
    }
  }

  /**
   * gif_add_frames().
   */
  function gif_add_frames($i, $d) {
    $locals_str = 13 + 3 * (2 << (ord($this->buffer[$i]{10}) & 0x07));
    $locals_end = strlen($this->buffer[$i]) - $locals_str - 1;
    $locals_tmp = substr($this->buffer[$i], $locals_str, $locals_end);
    $global_len = 2 << (ord($this->buffer[0]{10}) & 0x07);
    $locals_len = 2 << (ord($this->buffer[$i]{10}) & 0x07);
    $global_rgb = substr($this->buffer[0], 13, 3 * 2 << (
      ord($this->buffer[0]{10}) & 0x07)));
    $locals_rgb = substr($this->buffer[$i], 13, 3 * (2 << (
      ord($this->buffer[$i]{10}) & 0x07)));
    $locals_ext = "!\xF9\x04". chr(($this->disposal << 2) + 0) .
      chr(($d >> 0) & 0xFF) . chr(($d >> 8) & 0xFF) ."\x0\x0";
    if ($this->color > -1 && ord($this->buffer[$i]{10}) & 0x80) {
      for ($j = 0; $j < (2 << (ord($this->buffer[$i]{10}) & 0x07)); $j++) {
        if (ord($locals_rgb {3 * $j + 0}) == (($this->color >> 16) & 0xFF) &&
        ord($locals_rgb {3 * $j + 1}) == (($this->color >>  8) & 0xFF) &&
        ord($locals_rgb {3 * $j + 2}) == (($this->color >>  0) & 0xFF)) {
          $locals_ext = "!\xF9\x04" . chr(($this->disposal << 2) + 1) .
            chr(($d >> 0) & 0xFF) . chr(($d >> 8) & 0xFF) . chr($j) ."\x0";
          break;
        }
      }
    }
    switch ($locals_tmp{0}) {
      case "!":
        $locals_img = substr($locals_tmp, 8, 10);
        $locals_tmp = substr($locals_tmp, 18, strlen($locals_tmp) - 18);
        break;
      case ",":
        $locals_img = substr($locals_tmp, 0, 10);
        $locals_tmp = substr($locals_tmp, 10, strlen($locals_tmp) - 10);
        break;
    }
    if (ord($this->buffer[$i]{10}) & 0x80 && $this->image > -1) {
      if ($global_len == $locals_len) {
        if (drawing_gd_gif89a::gif_block_compare($global_rgb, $locals_rgb, $global_len)) {
          $this->gif .= ($locals_ext . $locals_img . $locals_tmp);
        }
        else {
          $byte  = ord($locals_img {9});
          $byte |= 0x80;
          $byte &= 0xF8;
          $byte |= (ord($this->buffer[0]{10}) & 0x07);
          $locals_img{9} = chr($byte);
          $this->gif .= ($locals_ext . $locals_img . $locals_rgb . $locals_tmp);
        }
      }
      else {
        $byte = ord($locals_img{9});
        $byte |= 0x80;
        $byte &= 0xF8;
        $byte |= (ord($this->buffer[$i]{10}) & 0x07);
        $locals_img{9} = chr($byte);
        $this->gif .= ($locals_ext . $locals_img . $locals_rgb . $locals_tmp);
      }
    }
    else {
      $this->gif .= ($locals_ext . $locals_img . $locals_tmp);
    }
    $this->image = 1;
  }

  /**
   * gif_add_footer().
   */
  function gif_add_footer() {
    $this->gif .= ";";
  }

  /**
   * gif_block_compare().
   */
  function gif_block_compare($global_block, $local_block, $length) {
    for ($i = 0; $i < $length; $i++) {
      if ($global_block {3 * $i + 0} != $local_block {3 * $i + 0} ||
      $global_block {3 * $i + 1} != $local_block {3 * $i + 1} ||
      $global_block {3 * $i + 2} != $local_block {3 * $i + 2}) {
        return FALSE;
      }
    }
    return TRUE;
  }

  /**
   * gif_word().
   */
  function gif_word($int) {
    return (chr($int & 0xFF) . chr(($int >> 8) & 0xFF));
  }

  /**
   * get_animation().
   */
  function get_animation() {
    return ($this->gif);
  }

}