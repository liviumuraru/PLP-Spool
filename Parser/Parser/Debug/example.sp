class A
{
    var a;
    var x, y ;
    var z; var t;
    integer fn f(My_type a, Your_type b);
};

class B inherit A
{
    var my_b;
    var my_c;
};

subclass C of B
{
    integer fn f(My_type a, Your_type b) overridden;
    integer fn my_fn(int b, bool c) final;
};

interface Interface_1
{
    integer fn do_something(A a, B ref b_ref);
}

interface Interface_2
{
    integer fn do_something_else(C ref c_ref, B ref b);
}

subclass final Last_subclass of C implements Interface_1, Interface_2
{
    integer fn do_something(A a, B ref b_ref) overridden
    {
        panic!("OUPS");
    }

    integer fn do_something_else(C ref c_ref, B ref b) overridden
    {
        panic!("WORKS");
    }
}

var a;
var    a,    b, c, d, ee, f, aed, wadafwda ;
 var c;

entry
{
    var a, b; var x  ;

    if 1 < 2
                                then a = 2;
                else a = 1;
    endif

    if 2 == 2
    then { a = 3; b = 4; }
    endif

    while 1 == 1
    {
        a = a + 1;
        break;
    }
    endloop

    for iter from 1 to 100 do
    {
        a = a + iter;
        continue;
    }
    endloop

    if 3 == 3 then panic!("OK?!"); endif

    C my_c_var;
    B my_b_var;
    A my_a_var_copy = my_c_var;
    ref A my_c_ref_as_A = C;
    my_c_var as type A.f();
    var my_c_var_copy = my_c_var;
    ref C my_c_var_ref = my_c_var;
    var my_c_var_copy_2 = my_c_var_ref;
}


exit
