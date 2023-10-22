/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include <bits/stdc++.h>
UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt();
    q = new UnlimitedInt(1);
}
UnlimitedInt *signchangernew(int *l1, int sizz, int ns)
{
    int *arr = new int[sizz];
    for (int i = 0; i < sizz; i++)
    {
        arr[i] = l1[i];
    }
    UnlimitedInt *obj = new UnlimitedInt(arr, sizz, ns, sizz);
    return obj;
}
UnlimitedInt *biggcd(UnlimitedInt *a, UnlimitedInt *b)
{
    if (b->get_sign() == 0)
    {
        UnlimitedInt *c = signchangernew(a->get_array(), a->get_size(), 1);
        return c;
    }
    UnlimitedInt *qq = a->mod(a, b);
    UnlimitedInt *ret = biggcd(b, qq);
    delete qq;
    return ret;
}
UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    if (num->get_sign() == 0 && den->get_sign() == 0)
    {
        p = new UnlimitedInt();
        q = new UnlimitedInt();
    }
    else
    {
        if (num->get_sign() == 0)
        {
            p = new UnlimitedInt();
            q = den;
        }
        else
        {
            if (den->get_sign() == 0)
            {
                p = new UnlimitedInt();
                q = new UnlimitedInt();
            }
            else
            {
                p = signchangernew(num->get_array(), num->get_size(), 1);
                q = signchangernew(den->get_array(), den->get_size(), 1);
                UnlimitedInt *P1 = signchangernew(num->get_array(), num->get_size(), 1);
                UnlimitedInt *Q1 = signchangernew(den->get_array(), den->get_size(), 1);
                UnlimitedInt *zhung = biggcd(P1, Q1);
                if (zhung->to_string() != "1")
                {
                    UnlimitedInt *random ;
                    random = random->div(p, zhung);
                    delete p;
                    p=random;
                    random = random->div(q, zhung);
                    delete q;
                    q=random;
                }
                delete zhung;
                delete P1;
                delete Q1;
                if (num->get_sign() * den->get_sign() != 1)
                {
                    UnlimitedInt*random;
                    random = signchangernew(p->get_array(), p->get_size(), num->get_sign());
                    delete p;
                    p=random;
                    random = signchangernew(q->get_array(), q->get_size(), den->get_sign());
                    delete q;
                    q=random;
                }
            }
        }
    }
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str()
{
    return get_p_str() + "/" + get_q_str();
}
UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *random = new UnlimitedInt();
    UnlimitedInt *num = random->add(random->mul(i1->get_p(), i2->get_q()), random->mul(i1->get_q(), i2->get_p()));
    UnlimitedInt *den = random->mul(i1->get_q(), i2->get_q());
    delete random;
    UnlimitedRational *ans = new UnlimitedRational(num, den);
    delete num;
    delete den;
    return ans;
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *random = new UnlimitedInt();
    UnlimitedInt *num = random->sub(random->mul(i1->get_p(), i2->get_q()), random->mul(i1->get_q(), i2->get_p()));
    UnlimitedInt *den = random->mul(i1->get_q(), i2->get_q());
    delete random;
    UnlimitedRational *ans = new UnlimitedRational(num, den);
    delete num;
    delete den;
    return ans;
}
UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *random = new UnlimitedInt();
    UnlimitedInt *num = random->mul(i1->get_p(), i2->get_p());
    UnlimitedInt *den = random->mul(i1->get_q(), i2->get_q());
    delete random;
    UnlimitedRational *ans = new UnlimitedRational(num, den);
    delete num;
    delete den;
    return ans;
}
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *random = new UnlimitedInt();
    UnlimitedInt *num = random->mul(i1->get_p(), i2->get_q());
    UnlimitedInt *den = random->mul(i1->get_q(), i2->get_p());
    delete random;
    UnlimitedRational *ans = new UnlimitedRational(num, den);
    delete num;
    delete den;
    return ans;
}
// #include<iostream>
// using namespace std;
// int main(){
//     UnlimitedRational* a = new UnlimitedRational(new UnlimitedInt("-18"),new UnlimitedInt("12"));
//     UnlimitedRational* b = new UnlimitedRational(new UnlimitedInt("-18"),new UnlimitedInt("-12"));
//     UnlimitedRational* c = new UnlimitedRational(new UnlimitedInt("288"),new UnlimitedInt("4378"));
//     UnlimitedRational* d =  UnlimitedRational::add(a,b);
//     UnlimitedRational* e = UnlimitedRational::div(a,d);
//     cout<<a->get_frac_str()<<endl;
//     cout<<b->get_frac_str()<<endl;
//     cout<<c->get_frac_str()<<endl;
//     cout<<d->get_frac_str()<<endl;
//     cout<<e->get_frac_str()<<endl;
// }
// int main(){
//     UnlimitedRational* a = new UnlimitedRational(new UnlimitedInt("526848"),new UnlimitedInt("815730721"));
//     UnlimitedRational* b = new UnlimitedRational(new UnlimitedInt(2),new UnlimitedInt(1));
//     UnlimitedRational* c = new UnlimitedRational(new UnlimitedInt(51),new UnlimitedInt(1));
//     UnlimitedRational* d =  UnlimitedRational::mul(a,a);
//     UnlimitedRational* e = UnlimitedRational::add(a,d);
//     cout<<a->get_frac_str()<<endl;
//     cout<<b->get_frac_str()<<endl;
//     cout<<c->get_frac_str()<<endl;
//     cout<<d->get_frac_str()<<endl;
//     cout<<e->get_frac_str()<<endl;
// }
// int main()
// {
//     UnlimitedInt *z = new UnlimitedInt();
//     UnlimitedInt *x = new UnlimitedInt("2");
//     UnlimitedInt *y = new UnlimitedInt("35");
//     UnlimitedRational *xx = new UnlimitedRational(x, y);
//     cout << xx->get_frac_str() << endl;
//     UnlimitedInt *x1 = new UnlimitedInt("5");
//     UnlimitedInt *y1 = new UnlimitedInt("2");
//     UnlimitedRational *xx1 = new UnlimitedRational(x1, y1);
//     cout<<xx->mul(xx,xx1)->get_frac_str()<<endl;
//     // UnlimitedInt*x1=new UnlimitedInt("-78");
//     // UnlimitedInt*y1=new UnlimitedInt("-104");
//     // cout<<x->div(x1,y1)->to_string()<<endl;
//     // UnlimitedInt*x2=new UnlimitedInt("-89");
//     // UnlimitedInt*y2=new UnlimitedInt("48");
//     // cout<<x->div(x2,y2)->to_string()<<endl;
//     // UnlimitedInt*x3=new UnlimitedInt("0");
//     // UnlimitedInt*y3=new UnlimitedInt("-88");
//     // cout<<x->div(x3,y3)->to_string()<<endl;
//     // UnlimitedInt*x4=new UnlimitedInt("192");
//     // UnlimitedInt*y4=new UnlimitedInt("96");
//     // cout<<x->div(x4,y4)->to_string()<<endl;
//     // UnlimitedRational *ru=new UnlimitedRational();
//     // UnlimitedRational*a=new UnlimitedRational(x,y);
//     // cout<<a->get_frac_str()<<endl;
//     // UnlimitedRational*b=new UnlimitedRational(z,w);
//     // cout<<b->get_frac_str()<<endl;
//     // cout<<a->add(a,b)->get_frac_str()<<endl;
//     // cout<<a->sub(a,b)->get_frac_str()<<endl;
//     // cout<<a->mul(a,b)->get_frac_str()<<endl;
//     // cout<<a->div(a,b)->get_frac_str()<<endl;
//     // cout<<ru->div(a,b)->get_frac_str()<<endl;
// }