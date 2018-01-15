10 + 2 + 10 + 100 + 10000000 - 10 * 100 / 100 - (100);
10 + 2;
3000 + (100 + 2) + 3 - 1 / 423;
var int my_int;
var float my_float;
my_int = 40;

type my_type
begin

var int my_int;

fn int my_function(var int i , var float f)
	begin

		var float my_inside_fn_float;
		my_inside_fn_float = 10.2;
		var int my_inside_fn_int;
		self.my_int = 100;

	end;

fn float my_function_noParam()
	begin
		var float my_inside_fn_float;
	end;

end;

subtype my_subtype inherit my_type
begin
	var int my_int;
end;

var int my_other_int;

fn my_type mytype_function()
	begin
		var float my_inside_fn_float;
	end;

fn my_type mytype_with_params(var int a, var float f)
	begin
		var float ok;
		var my_type temp;
		return temp;
	end;

entry

	var int my_int_main;
	my_int_main = 10041235123;
	call mytype_function();

	call mytype_with_params(100, 10);

	if 10 < 20 then
		call mytype_with_params(100, 10);
	endif;

	if 10 < 100 && 100 > 10 || 10 == 10 && 100 != 101 then
		my_int_main = 10;
		call mytype_with_params(100, 10);
		var char ok;
		var string str;
	else
		my_int_main = 100;
		call mytype_with_params(10, 100);
	endif;

	my_int_main = my_int_main + 1;
	my_int_main = my_int_main * 2;

	while 10 < 100 do
		my_int_main = 1 + 2;
	endloop;

	my_int_main = 1;

	var my_subtype my_subtyped_object;
	cast my_subtyped_object as my_type.my_int = 10;

end