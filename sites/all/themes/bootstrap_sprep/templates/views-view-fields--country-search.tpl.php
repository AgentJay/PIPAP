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
 * <?php print $fields['field_iso2']->content ?> 		<-- ISO2
 * <?php print $fields['field_country_name']->content ?>
 * <?php print $fields['field_iso3']->content ?>
 * <?php print $fields['field_country_marine_shortfall']->content ?>
 * <?php print $fields['field_country_prot_eez']->content ?>
 * <?php print $fields['field_country_prot_land']->content ?>
 * <?php print $fields['field_country_terra_shortfall']->content ?>
 *
 * @ingroup views_templates
 */
?>
<div class="rounded" >
<table class="tg">
  <tr>
    <th class="tg" colspan="4"><?php print $fields['field_country_name']->content ?> </th>
  </tr>
  <tr>
    <td class="tg" style="width: 100px;">ISO2: <?php print $fields['field_iso2']->content ?></td>
	<td class="tg" style="width: 200px;">Protected Land Percentage: <?php print $fields['field_country_prot_land']->content ?></td>
	<td class="tg" style="width: 200px;">Terrestrial Shortfall: <?php print $fields['field_country_terra_shortfall']->content ?></td>
  </tr>
  <tr>
    <td class="tg" style="width: 100px;">ISO3: <?php print $fields['field_iso3']->content ?></td>
	<td class="tg" style="width: 200px;">Protected Marine Percentage: <?php print $fields['field_country_prot_eez']->content ?></td>
	<td class="tg" style="width: 200px;">Marine Shortfall: <?php print $fields['field_country_marine_shortfall']->content ?></td>
  </tr>
</table>
</div>