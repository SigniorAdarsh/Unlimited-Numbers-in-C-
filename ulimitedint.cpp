/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <bits/stdc++.h>
UnlimitedInt::UnlimitedInt()
{
    unlimited_int = new int[1];
    capacity = 1;
    size = 1;
    sign = 0;
    for (int i = 0; i < 1; i++)
        unlimited_int[i] = 0;
}
UnlimitedInt *signchanger(int *l1, int sizz, int ns)
{
    int *arr = new int[sizz];
    for (int i = 0; i < sizz; i++)
    {
        arr[i] = l1[i];
    }
    UnlimitedInt *obj = new UnlimitedInt(arr, sizz, ns, sizz);
    return obj;
}
UnlimitedInt::UnlimitedInt(string s)
{
    if (s[0] == '0')
    {
        sign = 0;
        size = 1;
        capacity = 1;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
    }
    else
    {
        size = s.length();
        sign = 1;
        if (s[0] == '-')
        {
            sign = -1;
            size--;
        }
        unlimited_int = new int[size];
        capacity = size;
        if (sign == -1)
        {
            for (int i = size - 1; i >= 0; i--)
            {
                unlimited_int[size - 1 - i] = s[i + 1] - '0';
            }
        }
        else
        {
            for (int i = size - 1; i >= 0; i--)
            {
                unlimited_int[size - 1 - i] = s[i] - '0';
            }
        }
    }
}
int compareus(int *a1, int *b1, int len1, int len2)
{
    int i = 0;
    int j = 0;
    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;
    for (int k = 0; k < len1; k++)
    {
        if (a1[i + k] > b1[j + k])
            return 1;
        if (a1[i + k] < b1[j + k])
            return -1;
    }
    return 0;
}
void reverser(int *arr, int siz)
{
    for (int i = 0; i < siz / 2; i++)
    {
        swap(arr[i], arr[siz - 1 - i]);
    }
}
UnlimitedInt *divider(UnlimitedInt *a, UnlimitedInt *b, UnlimitedInt *&c)
{
    UnlimitedInt *dummy1;
    UnlimitedInt *dummy2;
    int *l1 = a->get_array();
    int *l2 = b->get_array();
    int siz1 = a->get_size();
    int siz2 = b->get_size();
    UnlimitedInt **storage = new UnlimitedInt *[10];
    int *temp = new int[1];
    temp[0] = 0;
    storage[0] = new UnlimitedInt(temp, 1, 0, 1);
    int i = 1;
    int *arr = new int[b->get_size()];
    for (int j = 0; j < b->get_size(); j++)
    {
        arr[j] = l2[j];
    }
    int sizer[10];
    sizer[0] = 1;
    storage[1] = new UnlimitedInt(arr, b->get_size(), 1, b->get_size());
    sizer[1] = siz2;
    i++;
    while (i < 10)
    {
        storage[i] = a->add(b, storage[i - 1]);
        sizer[i] = storage[i]->get_size();
        i++;
    }
    reverser(l1, a->get_size());
    reverser(l2, b->get_size());
    for (int aa = 0; aa < 10; aa++)
    {
        reverser(storage[aa]->get_array(), storage[aa]->get_size());
    }
    int *ans = new int[siz1];
    int *chuck;
    int aaa = 0;
    int lll = 0;
    int *rem = new int[1];
    int rsiz = 1;
    rem[0] = l1[0];
    int yz;
    for (; aaa < siz1; aaa++)
    {
        chuck = storage[1]->get_array();
        yz = compareus(chuck, rem, siz2, rsiz);
        if (yz > 0)
        {
            ans[lll] = 0;
            lll++;
            if (lll >= siz1)
                break;
            if (rem[0] != 0)
            {
                int *temp = new int[rsiz + 1];
                for (int ii = 0; ii < rsiz; ii++)
                {
                    temp[ii] = rem[ii];
                }
                temp[rsiz] = l1[lll];
                delete[] rem;
                rem = temp;
                rsiz++;
            }
            else
            {
                rem[0] = l1[lll];
            }
        }
        else
        {
            UnlimitedInt *rand;
            int bb;
            for (bb = 9; bb >= 1; bb--)
            {
                chuck = storage[bb]->get_array();
                yz = compareus(chuck, rem, storage[bb]->get_size(), rsiz);
                if (yz <= 0)
                    break;
            }
            ans[lll] = bb;
            lll++;
            reverser(rem, rsiz);
            dummy1 = new UnlimitedInt(rem, rsiz, 1, rsiz);
            reverser(chuck, storage[bb]->get_size());
            dummy2 = new UnlimitedInt(chuck, storage[bb]->get_size(), 1, storage[bb]->get_size());
            rand = dummy1->sub(dummy1, dummy2);
            rem = rand->get_array();
            rsiz = rand->get_size();
            delete dummy1;
            reverser(chuck, storage[bb]->get_size());
            reverser(rem, rsiz);
            if (lll >= siz1)
                break;
            if (rem[0] != 0)
            {
                int *temp = new int[rsiz + 1];
                for (int ii = 0; ii < rsiz; ii++)
                {
                    temp[ii] = rem[ii];
                }
                temp[rsiz] = l1[lll];
                delete[] rem;
                rem = temp;
                rsiz++;
            }
            else
            {
                rem[0] = l1[lll];
            }
        }
    }
    reverser(ans, siz1);
    reverser(rem, rsiz);
    c = new UnlimitedInt(rem, rsiz, 1, rsiz);
    for (i = siz1 - 1; i >= 0; i--)
    {
        if (ans[i] != 0)
            break;
    }
    if (i >= 0)
    {
        int *rans = new int[i + 1];
        for (int j = 0; j < i + 1; j++)
        {
            rans[j] = ans[j];
        }
        delete[] ans;
        ans = rans;
        UnlimitedInt *req = new UnlimitedInt(ans, i + 1, 1, i + 1);
        for (int t = 0; t < 10; t++)
        {
            delete storage[t];
        }
        delete[] storage;
        return req;
    }
    else
    {
        UnlimitedInt *req = new UnlimitedInt();
        for (int t = 0; t < 10; t++)
        {
            delete storage[t];
        }
        delete[] storage;
        return req;
    }
}
UnlimitedInt::UnlimitedInt(int i)
{
    if (i == 0)
    {
        sign = 0;
        size = 1;
        capacity = 1;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
    }
    else
    {
        sign = (i < 0) ? -1 : 1;
        int j = i * sign;
        int x = 0;
        while (j > 0)
        {
            j /= 10;
            x++;
        }
        if (sign == 0)
            size = 1;
        else
            size = x;
        capacity = size;
        unlimited_int = new int[capacity];
        x = 0;
        j = i * sign;
        while (j > 0)
        {
            unlimited_int[x] = j % 10;
            j /= 10;
            x++;
        }
    }
}
UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    unlimited_int = ulimited_int;
    capacity = cap;
    size = sz;
    sign = sgn;
}
UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}
int UnlimitedInt::get_sign()
{
    return sign;
}
int *UnlimitedInt::get_array()
{
    return unlimited_int;
}
int UnlimitedInt::get_size()
{
    return size;
}
int UnlimitedInt::get_capacity()
{
    return capacity;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int sgn = 0;
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();
    int sz = max(i1->get_size(), i2->get_size()) + 1;
    int *l1 = i1->get_array();
    int *l2 = i2->get_array();
    if (sgn1 * sgn2 == 0)
    {
        if (sgn1 == 0 && sgn2 == 0)
        {
            sgn = 0;
        }
        else
        {
            if (sgn1 == 0)
                sgn = sgn2;
            else
                sgn = sgn1;
        }
    }
    else
    {
        if (sgn1 * sgn2 == 1)
        {
            sgn = sgn1;
        }
        else
        {
            if (sgn1 == -1)
            {
                UnlimitedInt *i3 = signchanger(i1->get_array(), i1->get_size(), 1);
                UnlimitedInt *ans = sub(i2, i3);
                delete i3;
                return ans;
            }
            else
            {
                UnlimitedInt *i3 = signchanger(i2->get_array(), i2->get_size(), 1);
                UnlimitedInt *ans = sub(i1, i3);
                delete i3;
                return ans;
            }
        }
    }
    int *tempo = new int[sz];
    int carry = 0;
    for (int i = 0; i < sz; i++)
    {
        int x = (i < i1->get_size()) ? l1[i] : 0;
        int y = (i < i2->get_size()) ? l2[i] : 0;
        int z = x + y + carry;
        carry = (z > 9) ? (z / 10) : 0;
        z = z - carry * 10;
        tempo[i] = z;
    }
    if (tempo[sz - 1] == 0)
    {
        int *ntempo = new int[sz - 1];
        for (int i = 0; i < sz - 1; i++)
        {
            ntempo[i] = tempo[i];
        }
        delete[] tempo;
        UnlimitedInt *obj = new UnlimitedInt(ntempo, sz - 1, sgn, sz - 1);
        return obj;
    }
    else
    {
        UnlimitedInt *obj = new UnlimitedInt(tempo, sz, sgn, sz);
        return obj;
    }
}
UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int sgn = 0;
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();
    int sz = max(i1->get_size(), i2->get_size());
    int *l1 = i1->get_array();
    int *l2 = i2->get_array();
    if (sgn1 * sgn2 == 0)
    {
        if (sgn1 == 0 && sgn2 == 0)
        {
            sgn = 0;
        }
        else
        {
            if (sgn1 == 0)
            {
                UnlimitedInt *obj = signchanger(l2, i2->get_size(), -1 * sgn2);
                return obj;
            }
            else
            {
                UnlimitedInt *obj = signchanger(l1, i1->get_size(), sgn1);
                return obj;
            }
        }
    }
    else
    {
        if (sgn1 * sgn2 == 1)
        {
            sgn = sgn1;
        }
        else
        {
            if (sgn1 == -1)
            {
                UnlimitedInt *i3 = signchanger(i2->get_array(), i2->get_size(), -1);
                UnlimitedInt *ans = add(i1, i3);
                delete i3;
                return ans;
            }
            else
            {
                UnlimitedInt *i3 = signchanger(i2->get_array(), i2->get_size(), 1);
                UnlimitedInt *ans = add(i1, i3);
                delete i3;
                return ans;
            }
        }
    }
    if (sgn == -1)
    {

        UnlimitedInt *i3 = signchanger(i1->get_array(), i1->get_size(), 1);
        UnlimitedInt *i4 = signchanger(i2->get_array(), i2->get_size(), 1);
        UnlimitedInt *ans = sub(i4, i3);
        delete i3;
        delete i4;
        return ans;
    }
    else
    {
        int sz1 = i1->get_size();
        int sz2 = i2->get_size();
        if (sz1 < sz2)
        {
            UnlimitedInt *i3 = sub(i2, i1);
            i3->sign = -1 * i3->get_sign();
            return i3;
        }
        else
        {
            if (sz1 == sz2)
            {
                int i = sz1 - 1;
                while ((l1[i] == l2[i]) && (i >= 0))
                {
                    i--;
                }
                if (i == -1)
                {
                    UnlimitedInt *ans = new UnlimitedInt();
                    return ans;
                }
                else
                {
                    if (l1[i] < l2[i])
                    {
                        UnlimitedInt *i3 = sub(i2, i1);
                        UnlimitedInt *i4 = signchanger(i3->get_array(), i3->get_size(), -1);
                        delete i3;
                        return i4;
                    }
                    else
                    {
                        goto normal;
                    }
                }
            }
            else
            {
            normal:
                int *temp = new int[sz1];
                int carry = 0;
                for (int i = 0; i < sz1; i++)
                {
                    int x = (i < sz1) ? l1[i] : 0;
                    int y = (i < sz2) ? l2[i] : 0;
                    int z = x - y - carry;
                    carry = (z < 0) ? (1) : 0;
                    z = z + carry * 10;
                    temp[i] = z;
                }
                int i;
                for (i = sz1 - 1; i >= 0; i--)
                {
                    if (temp[i] != 0)
                        break;
                }
                int *tempo = new int[i + 1];
                for (int j = 0; j < i + 1; j++)
                {
                    tempo[j] = temp[j];
                }
                delete[] temp;
                UnlimitedInt *obj = new UnlimitedInt(tempo, i + 1, 1, i + 1);
                return obj;
            }
        }
    }
}
UnlimitedInt *addzero(int *arr, int sizz, int no0, int sgn)
{
    int *newarr = new int[sizz + no0];
    int i;
    for (i = 0; i < no0; i++)
    {
        newarr[i] = 0;
    }
    for (; i < sizz + no0; i++)
    {
        newarr[i] = arr[i - no0];
    }
    UnlimitedInt *ans = new UnlimitedInt(newarr, sizz + no0, sgn, sizz + no0);
    return ans;
}
UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *l1 = i1->get_array();
    int *l2 = i2->get_array();
    int siz2 = i2->get_size();
    int siz1 = i1->get_size();
    int sgn = i1->get_sign() * i2->get_sign();
    UnlimitedInt *I1 = signchanger(i1->get_array(), i1->get_size(), 1);
    UnlimitedInt *I2 = signchanger(i2->get_array(), i2->get_size(), 1);
    if (sgn == 0)
    {
        UnlimitedInt *ans = new UnlimitedInt();
        return ans;
    }
    int siz = I1->get_size() + I2->get_size();
    UnlimitedInt **storage = new UnlimitedInt *[10];
    int *temp = new int[1];
    temp[0] = 0;
    storage[0] = new UnlimitedInt(temp, 1, 0, 1);
    int i = 1;
    int *arr = new int[I1->get_size()];
    for (int j = 0; j < I1->get_size(); j++)
    {
        arr[j] = l1[j];
    }
    int sizer[10];
    sizer[0] = 0;
    storage[1] = new UnlimitedInt(arr, I1->get_size(), 1, I1->get_size());
    sizer[1] = siz1;
    i++;
    while (i < 10)
    {
        storage[i] = add(I1, storage[i - 1]);
        sizer[i] = storage[i]->get_size();
        i++;
    }
    UnlimitedInt *resoo;
    resoo = storage[I2->get_array()[0]];
    UnlimitedInt *too;
    for (int k = 1; k < siz2; k++)
    {
        too = addzero(storage[l2[k]]->get_array(), sizer[l2[k]], k, 1);
        resoo = add(resoo, too);
        delete too;
    }
    UnlimitedInt *resoo2 = signchanger(resoo->get_array(), resoo->get_size(), sgn);
    delete I1;
    delete I2;
    for (int t = 0; t < 10; t++)
    {
        delete storage[t];
    }
    delete[] storage;
    return resoo2;
}
UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *l1 = i1->get_array();
    int *l2 = i2->get_array();
    int siz1 = i1->get_size();
    int siz2 = i2->get_size();
    int *I1 = new int[siz1];
    int *I2 = new int[siz2];
    for (int i = 0; i < siz1; i++)
    {
        I1[i] = l1[i];
    }
    for (int i = 0; i < siz2; i++)
    {
        I2[i] = l2[i];
    }
    int sgnn = i1->get_sign() * i2->get_sign();
    UnlimitedInt *obj1 = new UnlimitedInt(I1, siz1, 1, siz1);
    UnlimitedInt *obj2 = new UnlimitedInt(I2, siz2, 1, siz2);
    if (i1->get_sign() == 0)
    {
        UnlimitedInt *ans = new UnlimitedInt();
        delete obj1;
        delete obj2;
        return ans;
    }
    if (siz1 < siz2 && sgnn == 1)
    {
        UnlimitedInt *ans = new UnlimitedInt();
        delete obj1;
        delete obj2;
        return ans;
    }
    if (siz1 < siz2 && sgnn == -1)
    {
        UnlimitedInt *ans = new UnlimitedInt(-1);
        delete obj1;
        delete obj2;
        return ans;
    }
    if (i1->get_sign() * i2->get_sign() >= 0)
    {
        UnlimitedInt *rem = new UnlimitedInt();
        UnlimitedInt *quot = divider(obj1, obj2, rem);
        delete obj1;
        delete obj2;
        delete rem;
        return quot;
    }
    else
    {
        UnlimitedInt *adder = new UnlimitedInt(1);
        UnlimitedInt *rem = new UnlimitedInt();
        UnlimitedInt *quota;
        UnlimitedInt *quot = divider(obj1, obj2, rem);
        if (rem->to_string() == "0")
        {
            quota = signchanger(quot->get_array(), quot->get_size(), -1);
            delete quot;
            quot = quota;
        }
        else
        {
            quota = quot->add(quot, adder);
            delete quot;
            quot = quota;
            quota = signchanger(quot->get_array(), quot->get_size(), -1);
            delete quot;
            quot = quota;
        }
        delete adder;
        delete rem;
        delete obj1;
        delete obj2;
        return quot;
    }
}
UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *a1 = div(i1, i2);
    UnlimitedInt *a2 = mul(i2, a1);
    UnlimitedInt *ans = sub(i1, a2);
    delete a1;
    delete a2;
    return ans;
}
string UnlimitedInt::to_string()
{
    string lullu = "";
    if (sign == 0)
    {
        lullu = "0";
    }
    else
    {
        if (sign == -1)
            lullu += "-";
        for (int i = 0; i < size; i++)
        {
            char ch = unlimited_int[size - i - 1] + '0';
            lullu += ch;
        }
    }
    return lullu;
}
// int main()
// {cout<<"start"<<endl;
//     for (int i=1;i<1000;i++)
//     {
//         for (int j=1;j<1000;j++)
//         {
//             //cout<<i<<" "<<j<<endl;
//             UnlimitedInt * n=new UnlimitedInt(-i);
//             UnlimitedInt * n2=new UnlimitedInt(j);
//             UnlimitedInt * n1=new UnlimitedInt();
//             n1=n1->add(n,n2);
//             if (n1->to_string()!=std::to_string((-i)+(j)))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)+(j))<<endl;
//                 cout<<i<<" "<<j<<"add"<<endl;
//                 break;
//             }
//             n1=n1->sub(n,n2);
//             if (n1->to_string()!=std::to_string((-i)-(j)))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)-(j))<<endl;
//                 cout<<i<<" "<<j<<"sub"<<endl;
//                 break;
//             }
//             n1=n1->mul(n,n2);
//             if (n1->to_string()!=std::to_string((-i)*(j)))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)*(j))<<endl;
//                 cout<<i<<" "<<j<<"mul"<<endl;
//                 break;
//             }
//             n1=n1->div(n,n2);
//             int ans=-i/j;
//             if (!(i%j==0))
//             {
//                 ans-=1;
//             }
//             if (n1->to_string()!=std::to_string(ans))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)/(j))<<endl;
//                 cout<<i<<" "<<j<<"div"<<endl;
//                 break;
//             }
//             delete n;
//             delete n1;
//             delete n2;
//         }
//     }
//     cout<<"pass"<<endl;
// }
// int main()
// {
//     UnlimitedInt *x = new UnlimitedInt("-13");
//     UnlimitedInt *y = new UnlimitedInt("12");
//     cout << x->div(x, y)->to_string() << endl;
//     cout << x->mul(x, y)->to_string() << endl;
//     cout << x->add(x, y)->to_string() << endl;
//     cout << x->sub(x, y)->to_string() << endl;
//     cout<<x->to_string()<<endl;
//     // UnlimitedInt*z=new UnlimitedInt("2");
//     // UnlimitedInt*w=new UnlimitedInt("0");
//     // cout<<x->to_string()<<endl;
//     // // cout<<y->to_string()<<endl;
//     // UnlimitedRational*ll=new UnlimitedRational(x,y);
//     // cout<<ll->get_frac_str()<<endl;
//     // cout<<x->to_string()<<endl;
//     // // cout<<y->to_string()<<endl;
//     // UnlimitedInt *r=new UnlimitedInt();
//     // UnlimitedInt*a1=r->add(x,y);
//     // // cout<<a1->to_string()<<endl;
//     // // cout<<r->add(x,y)->to_string()<<endl;
//     // // cout<<r->sub(x,y)->to_string()<<endl;
//     // // cout<<r->mul(x,y)->to_string()<<endl;
//     // // cout<<r->div(x,y)->to_string()<<endl;
//     // // cout<<"xx"<<endl;
//     // UnlimitedRational *ru=new UnlimitedRational();
//     // UnlimitedRational*a=new UnlimitedRational(x,y);
//     // UnlimitedRational*b=new UnlimitedRational(z,w);
//     // cout<<ru->div(a,b)->get_frac_str()<<endl;
// }