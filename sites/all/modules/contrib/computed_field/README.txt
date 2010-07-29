------------------The Computed Field Drupal Module----------------------------

Computed Field is a cck module which lets you add a computed field to custom
content types. You can choose whether to store your computed field in the
database. You can also choose whether to display the field, and how to format
it. The value of the field is set using php code, so it can draw on anything
available to drupal, including other fields, the current user, database
tables, etc. The drawback of this is of course that you need to know some php
to use it.

Computed Field requires the content module (cck).

-------------------------Update-------------------------------

As of 2006-8-11 the 'display format' setting has changed. You'll need to
update any existing computed fields: If your display format was 'This is the
value: %value', then change it to '$display = "This is the value: " .
$node_field_item['value'];'


-------------------------Usage--------------------------------

----------Getting Started-----------------------------------

Before you can use Computed Field, you'll need to get CCK and enable (at the
very least) the 'content' module. You will probably also want to enable the
other cck modules, such as 'text', 'number', 'date', etc.

To add a computed field to a content type, go to administer > content >
content types, select the content type you want to add to, and click on the
'add field' tab. One of the field types available should be 'Computed', and it
should have one bullet point under it, also labelled 'Computed'. If you select
this, give your field a name, and submit the form, you will get to the
configuration page for your new computed field.


--------Configuration---------------------------------------

A Computed Field can be configured with the usual cck field options, as well
as the following extra options:

Computed Code -- This is the code that will assign a value to your computed
field. It should be valid php without the <?php ?> tags.

Display this field -- Check this box to have this field appear on your node
view pages. You will usually want this unless you want your field to be a
hidden value.

Display Format -- This is also php code which should assign a string to the
$display variable. It has '$node_field_item['value']' available, which is the
value of the computed field. It also has '$field' available, and you can call
any drupal functions you want to display your field.

Store using the database settings below -- If this is checked then the field
is computed on node save and stored. If it isn't stored then it will be
recomputed every time you view a node containing this field.

Database Storage Settings
	Data Type -- This is the sql data type to use to store the field. Let us
	know if you need any other storage types, or if you would like an 'other'
	option :).

	Data Length -- This value will simply be passed on to sql. For storing up
	to 10 digit ints, enter 10. For storing currency as a float, use 10,2
	(unless you'll store larger than 10 figure amounts!).  For storing
	usernames or other short text with a varchar field, 64 may be appropriate.

	Default Value -- Leave this blank if you don't want the database to store
	a default value if your computed field's value isn't set.

	Not NULL -- Leave unchecked if you want to allow NULL values in the
	database field.

	Sortable  -- Used in Views to allow sorting a column of this field.


--------Examples------------------------------------------

Here are some usage examples to get you started with Computed
Field. 

-----Make a node link to itself-----------------

This example isn't very useful, but it demonstrates how to get
hold of the nid.

In your computed field's configuration:

- Computed Code:
// ensure the node has an id by saving it if it is new.
if (!$node->nid) node_save($node);
// store the nid in our computed field
$node_field[0]['value'] = $node->nid;

- Check 'Display this field'

- Display Format:
$display = l('A link to this node', 'node/'.$node_field_item['value']);

- Uncheck 'Store using the database settings below'. You could store this if
  you wanted to, but it's not costly to compute this field and is already
  stored in the node table. One reason why you may want to store it is if you
  want the value available to Views.

When you display a node of the content type containing this field it should
now have a link to itself.

-----Adding two other fields----------------------
Imagine you have two existing number fields, called field_product_price and
field_postage_price. You want to create a computed field field_total_cost
which adds these two fields. Create a new computed field with the name 'Total
Cost', and in your computed field's configuration set the following:

- Computed Code:
$node_field[0]['value'] =
$node->field_product_price[0]['value'] +
$node->field_postage_price[0]['value'];

- Check 'Display this field'

- Display Format:
$display = '$' . $node_field_item['value'];

- Check 'Store using the database settings below'

- Data Type: float

- Data Length: 10,2

- Default Value: 0.00

- Check 'Not NULL'

- Check 'Sortable'


-----Calculating a Duration given a start and end time-----

This example uses KarenS' date module (http://drupal.org/project/date) to
create two date fields field_start_time and field_end_time which record hours
and minutes. We then create a new computed field to work out the duration as a
decimal number of hours (so 1.5 is 1hour, 30minutes).

Computed field settings:

- Computed Code:
$start = $node->field_start_time[0]['value'];
$end = $node->field_end_time[0]['value'];
$start_decimal = $start['hours'] + ($start['minutes'] / 60);
$end_decimal = $end['hours'] + ($end['minutes'] / 60);
$node_field[0]['value'] = $end_decimal - $start_decimal;

- Check 'Display this field'</li>

- Display Format:</b><code>
$display = $node_field_item['value'] . " hours";

- Check 'Store using the database settings below

- Data Type:</b> float

- Data Length:</b> 3,2

- Check 'Sortable'

Now if you set the start time field to 9am and the end time to 11:30am, your
computed field will store the value '2.5' and display '2.5 hours'.


-----Send more examples!---------------------------------

If you have another useful (or instructive) example send it to me
(http://drupal.org/user/59132/contact) and I'll add it here for the benefit of
humankind.

-----------------------About Computed Field-----------------------------------
Computed Field was created by Agileware (http://www.agileware.net).

