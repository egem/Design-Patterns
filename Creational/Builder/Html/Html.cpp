#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

// Abstract Component: All HTML elements derive from this class
class HtmlElement {
public:
    virtual ~HtmlElement() = default;
    virtual std::string str() const = 0;
};

// Leaf Component: Basic HTML tags with content
class HtmlTag : public HtmlElement {
private:
    std::string tag;
    std::string content;

public:
    HtmlTag(const std::string& tag, const std::string& content)
        : tag(tag), content(content) {}

    std::string str() const override {
        return "<" + tag + ">" + content + "</" + tag + ">";
    }
};

// Composite Component: Can hold other HtmlElements (tags or other elements)
class HtmlComposite : public HtmlElement {
private:
    std::string tag;
    std::vector<std::shared_ptr<HtmlElement>> children;

public:
    HtmlComposite(const std::string& tag) : tag(tag) {}

    void addChild(std::shared_ptr<HtmlElement> element) {
        children.push_back(element);
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "<" << tag << ">";
        for (const auto& child : children) {
            oss << child->str(); // Render child elements
        }
        oss << "</" << tag << ">";
        return oss.str();
    }
};

// Abstract Builder: Abstract class for building HTML documents
class HtmlBuilder {
protected:
    HtmlComposite document;

public:
    HtmlBuilder(const std::string& rootTag) : document(rootTag) {}

    virtual void addTitle(const std::string& title) = 0;
    virtual void addHeader(const std::string& header) = 0;
    virtual void addParagraph(std::shared_ptr<HtmlElement> paragraph) = 0;
    virtual HtmlComposite getResult() const {
        return document;
    }
};

// Concrete Builder: Builds the HTML document
class ConcreteHtmlBuilder : public HtmlBuilder {
public:
    ConcreteHtmlBuilder(const std::string& rootTag) : HtmlBuilder(rootTag) {}

    void addTitle(const std::string& title) override {
        document.addChild(std::make_shared<HtmlTag>("title", title));
    }

    void addHeader(const std::string& header) override {
        document.addChild(std::make_shared<HtmlTag>("h1", header));
    }

    void addParagraph(std::shared_ptr<HtmlElement> paragraph) override {
        document.addChild(paragraph); // Use content projection here
    }
};

// Director: Directs the creation of HTML documents
class HtmlDirector {
private:
    HtmlBuilder& builder;

public:
    HtmlDirector(HtmlBuilder& builder) : builder(builder) {}

    void buildSimplePage() {
        builder.addTitle("Simple Page");
        builder.addHeader("Welcome to Simple Page");

        // Creating a paragraph with projected content (other HTML elements)
        auto paragraph = std::make_shared<HtmlComposite>("p");
        paragraph->addChild(std::make_shared<HtmlTag>("strong", "This is a simple paragraph with bold text."));
        builder.addParagraph(paragraph);
    }

    void buildComplexPage() {
        builder.addTitle("Complex Page");
        builder.addHeader("Complex Header");

        auto paragraph = std::make_shared<HtmlComposite>("p");
        paragraph->addChild(std::make_shared<HtmlTag>("em", "This is a complex paragraph with emphasized text."));
        paragraph->addChild(std::make_shared<HtmlTag>("a", "This is a link"));
        builder.addParagraph(paragraph);
    }
};

int main() {
    ConcreteHtmlBuilder builder("html");
    HtmlDirector director(builder);

    // Build a simple HTML page
    director.buildSimplePage();
    HtmlComposite simplePage = builder.getResult();
    std::cout << "Simple Page:\n" << simplePage.str() << std::endl;

    // Build a complex HTML page
    builder = ConcreteHtmlBuilder("html"); // Reset builder
    director.buildComplexPage();
    HtmlComposite complexPage = builder.getResult();
    std::cout << "Complex Page:\n" << complexPage.str() << std::endl;

    return 0;
}
