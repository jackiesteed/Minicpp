/********************************************************************
var.cpp, 主要是为了增加对多种数值类型的支持而添加的
目前支持bool, char, short, int, long, float, double
基本只使用long和double进行结算.
**********************************************************************/

#include <iostream>
#include <cmath>
#include <cassert>
#include "mccommon.h"
using namespace std;

extern vector<struct_type> struct_decls;

inline bool zero(double x)
{
    const double EPS = 1e-9;
    return abs(x) < EPS;
}
bool is_int_type(token_ireps type)
{
    if(type >= BOOL && type <= LONG) return true;
    return false;
}
bool is_float_type(token_ireps type)
{
    if(type >= FLOAT && type <= DOUBLE) return true;
    else return false;
}
bool check_valid_type(anonymous_var &val)
{
    if(!(is_int_type(val.var_type) || is_float_type(val.var_type))) return false;
    return true;
}
anonymous_var add(anonymous_var &a, anonymous_var &b)
{
    if(!check_valid_type(a) || !check_valid_type(b)) throw InterpExc(UNSUPPORTED_TYPE);
    anonymous_var res;
    if(a.var_type > b.var_type) res.var_type = a.var_type;
    else res.var_type = b.var_type;

    if(is_int_type(res.var_type))
    {
        res.int_value = a.int_value + b.int_value;
    }
    else
    {
        if(is_int_type(a.var_type))
        {
            res.float_value = double(a.int_value) + b.float_value;
        }
        else if(is_int_type(b.var_type))
        {
            res.float_value = a.float_value + double(b.int_value);
        }
        else
        {
            res.float_value = a.float_value + b.float_value;
        }
    }
    return res;
}

anonymous_var sub(anonymous_var &a, anonymous_var &b)
{
    if(!check_valid_type(a) || !check_valid_type(b)) throw InterpExc(UNSUPPORTED_TYPE);
    anonymous_var res;
    if(a.var_type > b.var_type) res.var_type = a.var_type;
    else res.var_type = b.var_type;

    if(is_int_type(res.var_type))
    {
        res.int_value = a.int_value - b.int_value;
    }
    else
    {
        if(is_int_type(a.var_type))
        {
            res.float_value = double(a.int_value) - b.float_value;
        }
        else if(is_int_type(b.var_type))
        {
            res.float_value = a.float_value - double(b.int_value);
        }
        else
        {
            res.float_value = a.float_value - b.float_value;
        }
    }
    return res;

}

anonymous_var mul(anonymous_var &a, anonymous_var &b)
{
    if(!check_valid_type(a) || !check_valid_type(b)) throw InterpExc(UNSUPPORTED_TYPE);
    anonymous_var res;

    if(a.var_type > b.var_type) res.var_type = a.var_type;
    else res.var_type = b.var_type;

    if(is_int_type(res.var_type))
    {
        res.int_value = a.int_value * b.int_value;
    }
    else
    {
        if(is_int_type(a.var_type))
        {
            res.float_value = double(a.int_value) * b.float_value;
        }
        else if(is_int_type(b.var_type))
        {
            res.float_value = a.float_value * double(b.int_value);
        }
        else
        {
            res.float_value = a.float_value * b.float_value;
        }
    }
    return res;
}

anonymous_var div(anonymous_var &a, anonymous_var &b)
{
    if(!check_valid_type(a) || !check_valid_type(b)) throw InterpExc(UNSUPPORTED_TYPE);
    anonymous_var res;
    if(a.var_type > b.var_type) res.var_type = a.var_type;
    else res.var_type = b.var_type;

    if(is_int_type(b.var_type))
    {
        if(0 == a.int_value) throw InterpExc(DIV_BY_ZERO);
    }
    else
    {
        if(zero(b.float_value)) throw InterpExc(DIV_BY_ZERO);
    }

    if(is_int_type(res.var_type))
    {
        res.int_value = a.int_value / b.int_value;
    }
    else
    {
        if(is_int_type(a.var_type))
        {
            res.float_value = double(a.int_value) / b.float_value;
        }
        else if(is_int_type(b.var_type))
        {
            res.float_value = a.float_value / double(b.int_value);
        }
        else
        {
            res.float_value = a.float_value / b.float_value;
        }
    }
    return res;
}


//因为现在我只用long 和double来存储表示所有的数值类型,
//在从控制台读取内容的时候会不方便, 现在先用
void cin_var(anonymous_var &v)
{
    switch (v.var_type)
    {
    case BOOL:
    {
        bool tmp_var;
        cin >> tmp_var;
        v.int_value = tmp_var;
        break;
    }
    case CHAR:
    {
        char tmp_var;
        cin >> tmp_var;
        v.int_value = tmp_var;
        break;
    }
    case SHORT:
    {
        short tmp_var;
        cin >> tmp_var;
        v.int_value = tmp_var;
        break;
    }
    case INT:
    {
        int tmp_var;
        cin >> tmp_var;
        v.int_value = tmp_var;
        break;
    }
    case LONG:
    {
        long tmp_var;
        cin >> tmp_var;
        v.int_value = tmp_var;
        break;
    }
    case FLOAT:
    {
        float tmp_var;
        cin >> tmp_var;
        v.float_value = tmp_var;
        break;
    }
    case DOUBLE:
    {
        double tmp_var;
        cin >> tmp_var;
        v.float_value = tmp_var;
        break;
    }
    default:
        throw InterpExc(UNSUPPORTED_TYPE);
        break;
    }
}


//输出的时候, 要先转化成相应的类型, 然后再打印
void cout_var(anonymous_var &v)
{
    switch(v.var_type)
    {
    case BOOL:
        cout << bool(v.int_value != 0);
        break;
    case CHAR:
        cout << char(v.int_value);
        break;
    case SHORT:
        cout << short(v.int_value);
        break;
    case INT:
        cout << int(v.int_value);
        break;
    case LONG:
        cout << long(v.int_value);
        break;
    case FLOAT:
        cout << float(v.float_value);
        break;
    case DOUBLE:
        cout << double(v.float_value);
        break;
    default:
        throw InterpExc(UNSUPPORTED_TYPE);
        break;
    }
}

bool is_valid_simple_type(token_ireps ti)
{
    return ti >= BOOL && ti <= DOUBLE;
}

void init_var(anonymous_var &v)
{
    v.int_value = 0;
    v.float_value = 0.0;
	v.struct_value.data.clear();
	//v.struct_value.type_name[0] = '\0';
	if(0 == strcmp(v.struct_value.type_name, "")) return;

	//如果是个结构体, 我们已经获得了结构体的名字了, 可以拿来指导初始化.
	int sz = struct_decls.size();
	for(int i = 0; i < sz; i++)
	{
		if(strcmp(v.struct_value.type_name, struct_decls[i].type_name) == 0)
		{
			int len = struct_decls[i].data.size();
			for(int j = 0; j < len; j++)
			{
				var member_var = struct_decls[i].data[j];
				v.struct_value.data.push_back(member_var);
			}
		}
	}
}

void neg_var(anonymous_var &v)
{
    if(is_int_type(v.var_type))
    {
        v.int_value = -v.int_value;
    }
    else if(is_float_type(v.var_type))
    {
        v.float_value = v.float_value;
    }
    else
    {
        throw InterpExc(UNSUPPORTED_TYPE);
    }
}

void abs_var(anonymous_var &v)
{
    if(is_int_type(v.var_type))
    {
        v.int_value = abs(v.int_value);
    }
    else if(is_float_type(v.var_type))
    {
        v.float_value = abs(v.float_value);
    }
    else
    {
        throw InterpExc(UNSUPPORTED_TYPE);
    }
}



int cmp(anonymous_var &a, anonymous_var &b)
{
    if(!check_valid_type(a) || !check_valid_type(b)) throw InterpExc(UNSUPPORTED_TYPE);
    if(is_int_type(a.var_type))
    {
        if(is_int_type(b.var_type))
        {
            if(a.int_value == b.int_value) return 0;
            if(a.int_value < b.int_value) return -1;
            return 1;
        }
        else if(is_float_type(a.var_type))
        {
            if(zero(a.int_value - b.float_value)) return 0;
            if(a.int_value < b.float_value) return -1;
            return 1;
        }
    }
    else
    {
        if(is_int_type(b.var_type))
        {
            if(zero(a.float_value - b.int_value)) return 0;
            if(a.float_value < b.int_value) return -1;
            return 1;
        }
        else
        {
            if(zero(a.float_value - b.float_value)) return 0;
            if(a.float_value < b.float_value) return -1;
            return 1;
        }
    }
	return 0;
}

bool get_bool_val(anonymous_var &v)
{
    bool bool_val = false;
    if(is_int_type(v.var_type))
    {
        bool_val = v.int_value != 0;
    }
    else if(is_float_type(v.var_type))
    {
        bool_val = !zero(v.float_value);
    }
    else
    {
        throw InterpExc(UNSUPPORTED_TYPE);
    }
    return bool_val;
}


//这个函数适配性地进行了赋值.
void adaptive_assign_var(anonymous_var &a, anonymous_var &b)
{
	if(a.var_type == STRUCT && b.var_type == STRUCT)
	{
		
		assert(0 == strcmp(a.struct_value.type_name, b.struct_value.type_name));
		assert(a.struct_value.data.size() == b.struct_value.data.size());
		int sz = b.struct_value.data.size();
		for(int i = 0; i < sz; i++)
		{
			adaptive_assign_var(a.struct_value.data[i].value, b.struct_value.data[i].value);
		}
		return;
	}
    if(!check_valid_type(a) || !check_valid_type(b)) throw InterpExc(UNSUPPORTED_TYPE);

    if(is_int_type(a.var_type))
    {
        if(is_int_type(b.var_type))
        {
            a.int_value = b.int_value;
        }
        else
        {
            a.int_value = int(b.float_value);
        }
    }
    else
    {
        if(is_int_type(b.var_type))
        {
            a.float_value = double(b.int_value);
        }
        else
        {
            a.float_value = b.float_value;
        }
    }
}