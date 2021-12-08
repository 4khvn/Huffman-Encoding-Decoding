#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
int frequency[128] = { 0 };
char arr[128] = { 0 };
static int check = 0;
string endcoded;
string decoded;
class node
{
public:
	int freq;
    string path;
	char a;
	node* left;
	node* right;
public:
	node()
	{

		int freq = 0;
		left = NULL;
		right = NULL;
	}
	node(int a, char b)
	{
        path = "";
		freq = a;
		this->a = b;
	}
};
class handle
{
public:
    node* root;
    node* tail;
public:
    handle()
    {
        root = NULL;
        tail = NULL;
    }
   node * insert(node * a,char b,int x)
    {
       node* temp = a;
       node* obj = new node(x, b);
        if (temp == NULL)
        {
           
            root = obj;
            return a;
        }
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        temp->right = obj;
        return temp;
    }
   node* insert1(node* a, char b, int x)
   {
       node* temp = a;
       node* obj = new node(x, b);
      
       while (temp != NULL)
       {
           if (temp->left == NULL)
           {
               temp->left = obj;
               return temp;
           }
           temp = temp->right;
       }
       return temp;
   }
   void print(node* a)
   {
       node* temp = a;
       while (temp != NULL)
       {
           cout << temp->left->a << temp->left->freq << endl;
           temp = temp->right;
       }
   }
};
void sorting(int count)
{
    int index = 0;
    for (int i = 1; i <= count; i++)
    {
        for (int j = i + 1; j <= count; j++)
        {
            if (frequency[i] > frequency[j])
            {
                int temp = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = temp;
                char temp1 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp1;
            }
        }
        
    }
}
string getcode(node* a, int i)
{
    node* temp = a;
    string temp1 = "";
    while (temp != NULL)
    {
        if (temp->left->a == arr[i])
        {
            temp1 += "0";
            temp->left->path = temp1;
            return temp1;
        }
        temp1 += "1" ;
        temp = temp->right;
    }

}
void decodingg(node* root, string s)
{
    node* temp = root;
    int x = s.length();
    for (int i = 0; i < x; i++)
    {
        if (temp != NULL)
        {
            if (s[i] == '0')
            {
                decoded += temp->left->a;
                 temp = root;
                continue;
            }
            temp = temp->right;
        }
       
    }
}
void encodingg(node *a,string s,int count,string *z)
{
   
    char temp1;
    fstream ptr;
    ptr.open(s.c_str(), ios::in);
    
        while (!ptr.fail())
        {
            node* temp = a;
            ptr.get(temp1);
            if (ptr.eof())
            {
                break;
            }
            while (temp != NULL)
            {
                if (temp->left->a == temp1)
                {
                    endcoded += temp->left->path;
                    break;
                }
                temp = temp->right;
            }
           

        }
    
}
int frequencyy(string a)
{
    char temp;
    fstream file;
    int count2 = 0;
    int flag;
    bool check = 0;
    file.open(a.c_str(), ios::in);
    while (!file.eof())
    {
        file.get(temp);
        flag = 0;
        check = 0;
        if (file.eof())
        {
            break;
        }
        while (flag <= count2)
        {
            if (arr[flag] == temp)
            {
                frequency[flag]++;
                check = 1;
            }
            flag++;
        }
        if (check == 0)
        {
            arr[flag] = temp;
            frequency[flag]++;
            count2++;
        }
    }
    file.close();
    return count2;
}
int main()
{
    string a = "Huffman_text.txt";
   int count =  frequencyy(a);
   check = count;
   sorting(count);
   handle obj;
    for (int i = 0; i<count; i++)
    {
        obj.insert(obj.root, 'i', i);
    }
    for (int i = 0; i < count; i++)
    {
        obj.insert1(obj.root,arr[check],frequency[check]);
        check--;
    }
    string* path = new string[count+1];
    for (int i = 1; i <= count; i++)
    {
        path[i] = getcode(obj.root, i);
    }
    for (int i =1 ; i <=count; i++)
    {
        cout << arr[i] << " " << frequency[i] << " " << path[i] << endl;
    }
    ofstream file("Table.txt");
    file << "Char | " << " " << "frequency | " << " " << "Path" << endl <<endl;
    for (int i = 1; i <= count; i++)
    {
        file << arr[i] << "| " << " " << frequency[i] << "| " << " " << path[i] << endl;
    }
    encodingg(obj.root,a, count, path);
    file << endl << "Encoded Text: " << endl << endcoded;
    decodingg(obj.root, endcoded);
    cout << endcoded << endl;
    cout << decoded;
    file << endl << "Decoded text: " << endl << decoded;
    file.close();
}