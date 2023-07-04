#include <iostream>
#include <vector>
#include <functional>
#include <Platform.Data.h>

using namespace Platform::Data;

template<std::integral TLinkAddress = std::uint64_t, LinksConstants<TLinkAddress> VConstants = LinksConstants<TLinkAddress>{true}, typename TLink = std::vector<TLinkAddress>, typename TReadHandler = std::function<TLinkAddress(TLink)>, typename TWriteHandler = std::function<TLinkAddress(TLink, TLink)>>
struct Links : public ILinks<LinksOptions<TLinkAddress, VConstants, TLink,TReadHandler, TWriteHandler>>
{
    using base = ILinks<LinksOptions<TLinkAddress, VConstants, TLink, TReadHandler, TWriteHandler>>;
    using typename base::LinkAddressType;
    using typename base::LinkType;
    using typename base::WriteHandlerType;
    using typename base::ReadHandlerType;
    using base::Constants;

    LinkAddressType Count(const std::vector<LinkAddressType>& restriction) const override { return 0; };

    LinkAddressType Each(const std::vector<LinkAddressType>& restriction, const ReadHandlerType& handler) const override { return 0; };

    LinkAddressType Create(const std::vector<LinkAddressType>& restriction, const WriteHandlerType& handler) override { return 0; };

    LinkAddressType Update(const std::vector<LinkAddressType>& restriction, const std::vector<LinkAddressType>& substitution, const WriteHandlerType& handler) override { return 0; };

    LinkAddressType Delete(const std::vector<LinkAddressType>& restriction, const WriteHandlerType& handler) override { return 0; };
};

void ILinksDeriverTest_ConstructorAndMethodsTest() {
    using TLinkAddress = uint64_t;
    using TLink = std::vector<TLinkAddress>;
    using TWriteHandler = std::function<TLinkAddress(TLink, TLink)>;
    using TReadHandler = std::function<TLinkAddress(TLink)>;
    Links<TLinkAddress> storage{};
    const Links<TLinkAddress> const_links {storage};
    const TLinkAddress linkAddress {1};
    
    Create(storage, linkAddress);
    Update(storage, TLink{1}, TLink{1, 1});
    storage.Count(TLink{1});
    const_links.Count(TLink{1});
    storage.Each(TLink{1}, [](const TLink& link){ return 1; });
    const_links.Each(TLink{1}, [](const TLink& link){ return 1; });
    Delete(storage, TLink{1});
}

int main() {
    ILinksDeriverTest_ConstructorAndMethodsTest();
    return 0;
}
