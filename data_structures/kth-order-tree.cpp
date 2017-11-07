#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct kthOrder
{
    int sz;
    int sizeOfSet;
    vector <int> elem;
    vector <int> nums;
    map <int, int> mapping;

    kthOrder(vector <int> &v)
    {
        nums = v;
        sz = nums.size();
        sizeOfSet = 0;

        elem.resize(2 * sz);


        sort(nums.begin(), nums.end());

        for (int i = 0; i < sz; i++)
        {
            mapping[v[i]] = lower_bound(nums.begin(), nums.end(), v[i]) - nums.begin();;
        }
    }


    void update(int p, int v)
    {
        p += sz;
        elem[p] += v;

        while (p >= 2)
        {
            elem[p >> 1] = elem[p]+ elem[p ^ 1];
            p >>= 1;
        }
    }


    void addElem(int n)
    {
        if (mapping.count(n) == 1)
        {
            update(mapping[n], 1);
            sizeOfSet++;
        }

    }
    void removeElem(int n)
    {
        if (mapping.count(n) == 1)
        {
            update(mapping[n], -1);
            sizeOfSet--;
        }
    }

    int getSize()
    {
        return sizeOfSet;
    }


    int query(int l, int r)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1) //if l is odd
            {
                acc = acc + elem[l];
                l++;
            }
            if (!(r & 1)) //if r is even
            {
                acc = acc + elem[r];
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        return acc;
    }

    int findKthGreatest(int k) //k is 0-indexed, assumes set has k-elements, returns 123412345 if k out of bounds
    {
        if (k >= getSize())
        {
            return 12341234;
        }
        k++;
        int left = 0;
        int right = sz - 1;

        while (left < right)
        {
            int mid = (left + right) / 2;
            int amtInLeft = query(left, mid);
            if (amtInLeft >= k)
            {
                right = mid;
            }
            else
            {
                k = k - amtInLeft;
                left = mid + 1;
            }
        }
        return nums[left];
    }

    int orderOfN(int n) //find 0-indexed position in the set of n-th element in original list (returns -1 if not in set)
    {
        int p = mapping[n];
        if (elem[p + sz] == 0)
        {
            return -1;
        }
        return query(0, p - 1);
    }

};


int main()
{
    vector <int> ourList = {100, -2, 3, 9, -5, 6, 5};
    kthOrder tree(ourList);
    tree.addElem(6);
    tree.addElem(3);
    tree.addElem(5);
    tree.addElem(3);

    cout<<tree.orderOfN(6)<<endl;
    cout<<tree.orderOfN(100)<<endl;
    cout<<tree.orderOfN(3)<<endl;
    cout<<tree.orderOfN(5)<<endl;
    cout<<tree.getSize()<<endl;
    for (int i = 0; i < tree.getSize() + 1; i++) //last i out of bounds
    {
        cout<<tree.findKthGreatest(i)<<endl;
    }
    cout<<"Set 2"<<endl;
    tree.addElem(100);
    tree.addElem(9);
    tree.addElem(9); //3, 3, 5, 6, 9, 9, 100
    cout<<tree.orderOfN(9)<<endl;
    cout<<tree.orderOfN(100)<<endl;
    for (int i = 0; i < tree.getSize(); i++)
    {
        cout<<tree.findKthGreatest(i)<<endl;
    }
    tree.removeElem(6);
    tree.removeElem(9);
    cout<<"after remove"<<endl;  //3, 3, 5, 9, 100
    cout<<tree.orderOfN(6)<<endl;
    cout<<tree.orderOfN(9)<<endl;
    cout<<tree.orderOfN(100)<<endl;
    for (int i = 0; i < tree.getSize(); i++)
    {
        cout<<tree.findKthGreatest(i)<<endl;
    }
    while(tree.getSize() > 1)
    {
       tree.removeElem(tree.findKthGreatest(tree.getSize() - 1));
    }
    for (int i = 0; i < tree.getSize(); i++)
    {
        cout<<tree.findKthGreatest(i)<<endl;
    }
}
