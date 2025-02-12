#include <iostream>
#include <cstdint>
#include <Platform.Collections.Methods.h>

template <std::size_t N, typename ...> class RecursionlessSizeBalancedTree;
template <std::size_t N, typename TElement> class RecursionlessSizeBalancedTree<N, TElement> : public Platform::Collections::Methods::Trees::RecursionlessSizeBalancedTreeMethods<RecursionlessSizeBalancedTree<N, TElement>, TElement>
{
    using base = Platform::Collections::Methods::Trees::RecursionlessSizeBalancedTreeMethods<RecursionlessSizeBalancedTree<N, TElement>, TElement>;
    friend base;
    friend base::base;

    struct TreeElement
    {
        public: TElement Size = 0;
        public: TElement Left = 0;
        public: TElement Right = 0;
    };

    private: TreeElement _elements[N] = { {0} };
    private: TElement _allocated = 0;

    public: TElement Root = 0;

    public: TElement Count() { return this->GetSizeOrZero(Root); }

    public: RecursionlessSizeBalancedTree() { _allocated = 1; }

    public: TElement Allocate()
    {
        auto newNode = _allocated;
        if (this->IsEmpty(newNode))
        {
            _allocated = _allocated + 1;
            return newNode;
        }
        else
        {
            throw std::runtime_error("Allocated tree element is not empty.");
        }
    }

    public: void Free(TElement node)
    {
        while (_allocated != 1 && this->IsEmpty(node))
        {
            auto lastNode = _allocated - 1;
            if (lastNode == node)
            {
                _allocated = lastNode;
                node = node - 1;
            }
            else
            {
                return;
            }
        }
    }

    public: bool IsEmpty(TElement node) { return iszero(this->GetElement(node), sizeof(TreeElement)); }

    protected: bool FirstIsToTheLeftOfSecond(TElement first, TElement second) { return first < second; }

    protected: bool FirstIsToTheRightOfSecond(TElement first, TElement second) { return first > second; }

    protected: TElement* GetLeftReference(TElement node) { return &GetElement(node)->Left; }

    protected: TElement GetLeft(TElement node) { return this->GetElement(node)->Left; }

    protected: TElement* GetRightReference(TElement node) { return &GetElement(node)->Right; }

    protected: TElement GetRight(TElement node) { return this->GetElement(node)->Right; }

    protected: TElement GetSize(TElement node) { return this->GetElement(node)->Size; }

    protected: void SetLeft(TElement node, TElement left) { this->GetElement(node)->Left = left; }

    protected: void SetRight(TElement node, TElement right) { this->GetElement(node)->Right = right; }

    protected: void SetSize(TElement node, TElement size) { this->GetElement(node)->Size = size; }

    private: TreeElement* GetElement(TElement node) { return &_elements[node]; }
};

int main()
{
    RecursionlessSizeBalancedTree<10000, std::uint32_t> recursionlessSizeBalancedTree;
    std::cout << "Success" << std::endl;
    return 0;
}

