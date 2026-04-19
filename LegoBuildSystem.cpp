#include <iostream>
using namespace std;

//_________________________________________________implementation of the class Block
class Block
{
    string shape;
    string color;

public:
    Block(string shape = "", string color = "")
    {
        if ((shape == "ObliquedL" || shape == "obliquedL") || (shape == "ObliquedR" || shape == "obliquedR") || (shape == "Simple" || shape == "simple" || shape == ""))
        {
            this->shape = shape;
        }
        else
        {
            cout << "invalid input for the shape:" << endl
                 << "shapes can be only ObliquedL, ObliquedR or Simple" << endl;
        }

        if (color == "red" || color == "Red" || color == "white" || color == "White" || color == "")
        {
            this->color = color;
        }
        else
        {
            cout << "invalid input for the color" << endl
                 << "color can be 'red', 'white' or neither";
        }
    }

    ostream &display(ostream &out) const
    {
        if (this->shape == "ObliquedL" || this->shape == "obliquedL")
        {
            if (this->color == "white" || this->color == "White")
            {
                out << "(ObliquedL, White) ";
            }
            else if (this->color == "red" || this->color == "Red")
            {
                out << "(ObliquedL, Red) ";
            }
            else if (this->color == "")
            {
                out << "(ObliquedL)  ";
            }
        }
        else if (this->shape == "ObliquedR" || this->shape == "obliquedR")
        {
            if (this->color == "white" || this->color == "White")
            {
                out << "(ObliquedR, White) ";
            }
            else if (this->color == "red" || this->color == "Red")
            {
                out << "(ObliquedR, Red) ";
            }
            else if (this->color == "")
            {
                out << "(ObliquedR)  ";
            }
        }
        else if (this->shape == "Simple" || this->shape == "simple")
        {
            if (this->color == "white" || this->color == "White")
            {
                out << "(Simple, White) ";
            }
            else if (this->color == "red" || this->color == "Red")
            {
                out << "(Simple, Red) ";
            }
            else if (this->color == "")
            {
                out << "(Simple)  ";
            }
        }
        else if (shape == "" && color == "")
        {
            out << "";
        }
        else
        {
            out << "Invalid shape";
        }
        return out;
    }

    friend ostream &operator<<(ostream &out, const Block &b);
};
ostream &operator<<(ostream &out, const Block &b)
{
    return b.display(out);
}

//_________________________________________________implementation of the class Build
class Build
{
    int height;
    int depth;
    int width;
    Block ***Content;

public:
    Build(const Block &b)
    {
        height = 1;
        depth = 1;
        width = 1;
        // i is used for height, j for depth and k for width as shown in figure-1 in instructions
        this->Content = nullptr;
        this->Content = new Block **[this->height];
        for (size_t i = 0; i < (this->height); i++)
        {
            *(this->Content + i) = new Block *[this->depth];
            for (size_t j = 0; j < (this->depth); j++)
            {
                *(*(this->Content + i) + j) = new Block[this->width];
            }
        }
        (*(*(*(this->Content + 0) + 0) + 0)) = b;
    }
    ostream &display(ostream &out) const
    {
        // int temp_height = this->height;
        for (int i = (this->height - 1); i >= 0; i--)
        {
            out << "Layer " << i << ": " << endl;
            // temp_height = temp_height - 1;
            for (size_t j = 0; j < depth; j++)
            {
                for (size_t k = 0; k < width; k++)
                {
                    (*(*(*(this->Content + i) + j) + k)).Block::display(out);
                }
                out << endl;
            }
        }
        return out;
    }
    friend ostream &operator<<(ostream &out, const Build &b);
    void operator^=(const Build &b)
    {
        int newHeight = this->height + b.height;
        int newDepth;
        int newWidth;
        if(this->depth >= b.depth)
        {
            newDepth = this->depth;
        }
        else
        {
            newDepth = b.depth;
        }
        if(this->width >= b.width)
        {
            newWidth = this->width;
        }
        else
        {
            newWidth = b.width;
        }

        Block ***newContent = new Block **[newHeight];
        for (int i = 0; i < newHeight; i++)
        {
            newContent[i] = new Block *[newDepth];
            for (int j = 0; j < newDepth; j++)
            {
                newContent[i][j] = new Block[newWidth];
            }
        }

        // Copy the blocks from the original content to the new content
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                for (int k = 0; k < this->width; k++)
                {
                    newContent[i][j][k] = this->Content[i][j][k];
                }
            }
        }

        // Add the blocks from the new content on top of the original content
        for (int i = 0; i < b.height; i++)
        {
            for (int j = 0; j < b.depth; j++)
            {
                for (int k = 0; k < b.width; k++)
                {
                    newContent[this->height + i][j][k] = b.Content[i][j][k];
                }
            }
        }

        // Delete the old content and update the fields
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                delete[] this->Content[i][j];
            }
            delete[] this->Content[i];
        }
        delete[] this->Content;

        this->Content = newContent;
        this->height = newHeight;
        this->depth = newDepth;
        this->width = newWidth;
    }

    Build operator^(const Build &b)
    {
        int newHeight = this->height + b.height;
        int newDepth;
        int newWidth;
        if(this->depth >= b.depth)
        {
            newDepth = this->depth;
        }
        else
        {
            newDepth = b.depth;
        }
        if(this->width >= b.width)
        {
            newWidth = this->width;
        }
        else
        {
            newWidth = b.width;
        }

        Block ***newContent = new Block **[newHeight];
        for (int i = 0; i < newHeight; i++)
        {
            newContent[i] = new Block *[newDepth];
            for (int j = 0; j < newDepth; j++)
            {
                newContent[i][j] = new Block[newWidth];
            }
        }

        // Copy the blocks from the original content to the new content
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                for (int k = 0; k < this->width; k++)
                {
                    newContent[i][j][k] = this->Content[i][j][k];
                }
            }
        }

        // Add the blocks from the new content on top of the original content
        for (int i = 0; i < b.height; i++)
        {
            for (int j = 0; j < b.depth; j++)
            {
                for (int k = 0; k < b.width; k++)
                {
                    newContent[this->height + i][j][k] = b.Content[i][j][k];
                }
            }
        }

        Block t("", "");
        Build return_obj(t);
        for (int i = 0; i < return_obj.height; i++)
        {
            for (int j = 0; j < return_obj.depth; j++)
            {
                delete[] return_obj.Content[i][j];
            }
            delete[] return_obj.Content[i];
        }
        delete[] return_obj.Content;

        return_obj.Content = newContent;
        return_obj.height = newHeight;
        return_obj.depth = newDepth;
        return_obj.width = newWidth;
        return return_obj;
    }

    void operator-=(const Build &b)
    {
        if(b.height < this->height)
        {
            cout<<"the height of the content is smaller than the original content"<<endl;
            return;
        }
        int newHeight = this->height;
        int newDepth = this->depth + b.depth;
        int newWidth;
        if (this->width > b.width)
            newWidth = this->width;
        else
            newWidth=b.width;
        //int newWidth = this->width + b.width;

        Block ***newContent = new Block **[newHeight];
        for (int i = 0; i < newHeight; i++)
        {
            newContent[i] = new Block *[newDepth];
            for (int j = 0; j < newDepth; j++)
            {
                newContent[i][j] = new Block[newWidth];
            }
        }

        // Copy the blocks from the original content to the new content
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                for (int k = 0; k < this->width; k++)
                {
                    newContent[i][j][k] = this->Content[i][j][k];
                }
            }
        }

        // Add the blocks from the new content to back of the original content
        for (int i = 0; i < b.height; i++)
        {
            for (int j = 0; j < b.depth; j++)
            {
                for (int k = 0; k < b.width; k++)
                {
                    newContent[i][this->depth + j][k] = b.Content[i][j][k];
                }
            }
        }

        // Delete the old content and update the fields
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                delete[] this->Content[i][j];
            }
            delete[] this->Content[i];
        }
        delete[] this->Content;

        this->Content = newContent;
        this->height = newHeight;
        this->depth = newDepth;
        this->width = newWidth;
    }
    Build operator-(const Build&b)
    {
        if(b.height < this->height)
        {
            cout<<"the height of the content is smaller than the original content"<<endl;
            return *this;
        }
        int newHeight = this->height;
        int newDepth = this->depth + b.depth;
        int newWidth = this->width + b.width;

        Block ***newContent = new Block **[newHeight];
        for (int i = 0; i < newHeight; i++)
        {
            newContent[i] = new Block *[newDepth];
            for (int j = 0; j < newDepth; j++)
            {
                newContent[i][j] = new Block[newWidth];
            }
        }

        // Copy the blocks from the original content to the new content
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                for (int k = 0; k < this->width; k++)
                {
                    newContent[i][j][k] = this->Content[i][j][k];
                }
            }
        }

        // Add the blocks from the new content to back of the original content
        for (int i = 0; i < b.height; i++)
        {
            for (int j = 0; j < b.depth; j++)
            {
                for (int k = 0; k < b.width; k++)
                {
                    newContent[i][this->depth + j][k] = b.Content[i][j][k];
                }
            }
        }

        Block t("", "");
        Build return_obj(t);
        for (int i = 0; i < return_obj.height; i++)
        {
            for (int j = 0; j < return_obj.depth; j++)
            {
                delete[] return_obj.Content[i][j];
            }
            delete[] return_obj.Content[i];
        }
        delete[] return_obj.Content;

        return_obj.Content = newContent;
        return_obj.height = newHeight;
        return_obj.depth = newDepth;
        return_obj.width = newWidth;
        return return_obj;
    }

    void operator+=(const Build &b)
    {
        if((b.height < this->height) || (b.depth < this->depth))
        {
            cout<<"the height of the content is smaller than the original content"<<endl;
            return;
        }
        int newHeight = this->height;
        int newDepth = this->depth;
        int newWidth = this->width + b.width;

        Block ***newContent = new Block **[newHeight];
        for (int i = 0; i < newHeight; i++)
        {
            newContent[i] = new Block *[newDepth];
            for (int j = 0; j < newDepth; j++)
            {
                newContent[i][j] = new Block[newWidth];
            }
        }

        // Copy the blocks from the original content to the new content
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                for (int k = 0; k < this->width; k++)
                {
                    newContent[i][j][k] = this->Content[i][j][k];
                }
            }
        }

        // Add the blocks from the new content to back of the original content
        for (int i = 0; i < b.height; i++)
        {
            for (int j = 0; j < b.depth; j++)
            {
                for (int k = 0; k < b.width; k++)
                {
                    newContent[i][j][this->width + k] = b.Content[i][j][k];
                }
            }
        }

        // Delete the old content and update the fields
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                delete[] this->Content[i][j];
            }
            delete[] this->Content[i];
        }
        delete[] this->Content;

        this->Content = newContent;
        this->height = newHeight;
        this->depth = newDepth;
        this->width = newWidth;
    }

    Build operator+(const Build &b)
    {
        if((b.height < this->height) || (b.depth < this->depth))
        {
            cout<<"the height of the content is smaller than the original content"<<endl;
            return *this;
        }
        int newHeight = this->height;
        int newDepth = this->depth + b.depth;
        int newWidth = this->width + b.width;

        Block ***newContent = new Block **[newHeight];
        for (int i = 0; i < newHeight; i++)
        {
            newContent[i] = new Block *[newDepth];
            for (int j = 0; j < newDepth; j++)
            {
                newContent[i][j] = new Block[newWidth];
            }
        }

        // Copy the blocks from the original content to the new content
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->depth; j++)
            {
                for (int k = 0; k < this->width; k++)
                {
                    newContent[i][j][k] = this->Content[i][j][k];
                }
            }
        }

        // Add the blocks from the new content to back of the original content
        for (int i = 0; i < b.height; i++)
        {
            for (int j = 0; j < b.depth; j++)
            {
                for (int k = 0; k < b.width; k++)
                {
                    newContent[i][j][this->width + k] = b.Content[i][j][k];
                }
            }
        }

        Block t("", "");
        Build return_obj(t);
        for (int i = 0; i < return_obj.height; i++)
        {
            for (int j = 0; j < return_obj.depth; j++)
            {
                delete[] return_obj.Content[i][j];
            }
            delete[] return_obj.Content[i];
        }
        delete[] return_obj.Content;

        return_obj.Content = newContent;
        return_obj.height = newHeight;
        return_obj.depth = newDepth;
        return_obj.width = newWidth;
        return return_obj;
    }

    // multiplication operator
friend Build operator*(unsigned int n, Build const& a) {
    Build result = a;
    for (unsigned int i = 1; i < n; i++) {
        result += a;
    }
    return result;
}

// division operator
friend Build operator/(unsigned int n, Build const& a) {
    Build result = a;
    for (unsigned int i = 1; i < n; i++) {
        result ^= a;
    }
    return result;
}

// modulo operator
friend Build operator%(unsigned int n, Build const& a) {
    Build result = a;
    for (unsigned int i = 1; i < n; i++) {
        result -= a;
    }
    return result;
}
};
ostream &operator<<(ostream &out, const Build &t)
{
    return t.display(out);
}
/*-------------------------Main----------------------------------*/
int main()
{
    Block b1("obliquedL", "white");
    Block b2("obliquedL","red");
    Block b3("obliquedR", "red");
    Block b4("obliquedR", "white");
    Block b5("simple", "white");
    Block b6("simple", "red");

    Build t1(b1);
    Build t2(b2);
    Build t3(b3);
    Build t4(b4);    
    Build t5(b5);
    Build t6(b6);

    cout<<"t1^=t2"<<endl;
    t1^=t2;
    cout<<"t1 "<<t1<<endl<<endl;

    cout<<"t1+=t3"<<endl;
    t1+=t3;
    cout<<"t1 "<<t1<<endl<<endl;

    cout<<"t1+=t4"<<endl;
    t1+=t4;
    cout<<"t1 "<<t1<<endl<<endl;

}