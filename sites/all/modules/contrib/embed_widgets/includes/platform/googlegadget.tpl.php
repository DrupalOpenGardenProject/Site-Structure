<?php
// $Id: googlegadget.tpl.php,v 1.2 2009/05/15 21:16:29 jtsnow Exp $

/**
 * @file embed_widgets_google_gadgets.tpl.php
 * Default theme implementation to of Google Gadget XML.
 *
 * Available variables:
 * - $title: The Gadget title.
 * - $title_url: The URL the title links to.
 * - $description: A description of the gadget.
 * - $height: Gadget height in pixels.
 * - $width: Gadget width in pixels.
 * - $screenshot: URL to a screenshot of the gadget.
 * - $thumbnail: URL to a thumbnail of the gadget.
 * - $author: Author of the gadget.
 * - $author_email: Author's e-mail.
 * - $author_location: Author's location.
 * - $url: URL of the embedded content.
 *
 * @see template_preprocess_embed_widgets_google_gadgets()
 */

?>
<?php print '<?xml version="1.0" encoding="UTF-8"?>' ?>
<Module>
<ModulePrefs title="<?php print $title ?>" 
    <?php if ($title_url) { ?>
    title_url="<?php print $title_url ?>" 
    <?php } ?>
    <?php if ($description) { ?>
    description="<?php print $description ?>" 
    <?php } ?>
    height="<?php print $height ?>" 
    width="<?php print $width ?>"
    <?php if ($screenshot) { ?>
    screenshot="<?php print $screenshot ?>" 
    <?php } ?>
    <?php if ($thumbnail) { ?>
    thumbnail="<?php print $thumbnail ?>" 
    <?php } ?>
    <?php if ($author) { ?>
    author="<?php print $author ?>" 
    <?php } ?>
    <?php if ($author_email) { ?>
    author_email="<?php print $author_email ?>" 
    <?php } ?>
    <?php if ($author_location) { ?>
    author_location="<?php print $author_location ?>" 
    <?php } ?>
    <?php if ($author_affiliation) { ?>
    author_affiliation="<?php print $author_affiliation ?>" 
    <?php } ?> />
<Content type="url" href="<?php print $url ?>" />
</Module>
