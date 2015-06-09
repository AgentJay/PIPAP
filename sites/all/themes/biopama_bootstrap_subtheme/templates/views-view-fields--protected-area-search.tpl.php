<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * <?php print $fields['title']->content ?> 		<-- WDPA ID
 * <?php print $fields['field_protected_area_name']->content ?>
 * <?php print $fields['field_protected_area_name-value']->content ?>
 * <?php print $fields['field_protected_area_designation']->content ?>
 * <?php print $fields['field_protected_area_iucn_cat']->content ?>
 *
 * @ingroup views_templates
 */
?>
<div class="rounded" >
<table class="tg">
  <tr>
    <th class="tg" colspan="4"><?php print $fields['field_protected_area_name']->content ?> </th>
  </tr>
  <tr>
    <td class="tg" style="width: 200px;">Protected Area ID: <?php print $fields['title']->content ?></td>
	<td class="tg" style="width: 200px;">IUCN Category: <?php print $fields['field_protected_area_iucn_cat']->content ?></td>
	<td class="tg" style="width: 200px;">Designation: <?php print $fields['field_protected_area_designation']->content ?></td>
	<td class="tg">Country: <?php print $fields['field_country_name']->content ?></td>
  </tr>
</table>
</div>