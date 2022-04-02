#include "GumboParserAdapter.hpp"

#include "gumbo.h"

#include <fmt/core.h>

namespace {
USING_QTC_NAMESPACE

} // namespace

struct GumboParserAdapter::Impl {
    explicit Impl() = default;
    ~Impl() {
        if (_rootNode) {
            gumbo_destroy_output(&kGumboDefaultOptions, _rootNode);
        }
    }

    Result Parse(std::string const &data) {
        _data = data.substr(data.find("<head>"));

        if (_rootNode) {
            gumbo_destroy_output(&kGumboDefaultOptions, _rootNode);
            _rootNode = nullptr;
        }
        _rootNode = gumbo_parse(_data.c_str());
        if (!_rootNode) {
            return Result(Result::Success::No, "Could not parse data");
        }
        return Result(Result::Success::Yes);
    }

    std::vector<std::string> GetAllLinks() {
        std::vector<std::string> vec;
        SearchForLinks(_rootNode->root, &vec);
        return vec;
    }

private:
    static void SearchForLinks(GumboNode *node, std::vector<std::string> *vec) {
        if (node->type != GUMBO_NODE_ELEMENT) {
            return;
        }
        GumboAttribute *href;
        if (node->v.element.tag == GUMBO_TAG_A && (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
            fmt::print("Found link {}\n", href->value);
            vec->push_back(href->value);
        }

        GumboVector *children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            SearchForLinks(static_cast<GumboNode *>(children->data[i]), vec);
        }
    }

private:
    GumboOutput *_rootNode{nullptr};
    std::string _data;
};

GumboParserAdapter::GumboParserAdapter()
    : _impl(std::make_unique<Impl>()) {}

GumboParserAdapter::~GumboParserAdapter() = default;

Result GumboParserAdapter::Parse(std::string const &data) {
    return _impl->Parse(std::move(data));
}

std::vector<std::string> GumboParserAdapter::GetAllLinks() {
    return _impl->GetAllLinks();
}
