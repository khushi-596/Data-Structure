#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

struct Node {
    string imagePath;
    Node* next;
    Node* prev;
    Node(string path) : imagePath(path), next(nullptr), prev(nullptr) {}
};

struct Button {
    sf::RectangleShape shape;
    sf::Text label;
    sf::Color normalColor = sf::Color(52, 73, 94);
    sf::Color hoverColor = sf::Color(41, 128, 185);

    Button(const std::string& text, sf::Vector2f pos, sf::Font& font) {
        shape.setSize({140, 45});
        shape.setPosition(pos);
        shape.setFillColor(normalColor);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = label.getLocalBounds();
        label.setPosition(
            pos.x + (shape.getSize().x - textBounds.width) / 2 - textBounds.left,
            pos.y + (shape.getSize().y - textBounds.height) / 2 - textBounds.top - 4
        );
    }

    void updateHover(const sf::Vector2i& mousePos) {
        shape.setFillColor(shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) ? hoverColor : normalColor);
    }

    bool isClicked(const sf::Vector2i& mousePos) {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }
};

class ImageViewer {
    Node* current = nullptr;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    void insertImage(const std::string& path) {
        Node* newNode = new Node(path);
        if (!current) {
            newNode->next = newNode->prev = newNode;
            current = newNode;
        } else {
            Node* last = current->prev;
            last->next = newNode;
            newNode->prev = last;
            newNode->next = current;
            current->prev = newNode;
        }
        loadCurrentImage();
    }

    void deleteImage() {
        if (!current) return;
        Node* toDelete = current;
        if (current->next == current) {
            delete toDelete;
            current = nullptr;
        } else {
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            current = toDelete->next;
            delete toDelete;
        }
        if (current) loadCurrentImage();
    }

    void nextImage() {
        if (current) {
            current = current->next;
            loadCurrentImage();
        }
    }

    void prevImage() {
        if (current) {
            current = current->prev;
            loadCurrentImage();
        }
    }

    void loadCurrentImage() {
        if (!current || !texture.loadFromFile(current->imagePath)) {
            std::cout << "Failed to load image.\n";
            return;
        }

        sprite.setTexture(texture);

        float maxWidth = 700.f, maxHeight = 500.f;
        float imgWidth = static_cast<float>(texture.getSize().x);
        float imgHeight = static_cast<float>(texture.getSize().y);
        float scale = std::min(maxWidth / imgWidth, maxHeight / imgHeight);

        sprite.setScale(scale, scale);
        float finalWidth = imgWidth * scale;
        float finalHeight = imgHeight * scale;

        sprite.setPosition((800 - finalWidth) / 2.f, (600 - finalHeight) / 2.f);
    }

    bool hasImage() const {
        return current != nullptr;
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    std::string getCurrentImageName() const {
        return current ? current->imagePath : "";
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Image Viewer");
    ImageViewer viewer;

    viewer.insertImage("images/img1.jpeg");
    viewer.insertImage("images/img2.jpeg");
    viewer.insertImage("images/img3.jpeg");

    sf::Font font;
    if (!font.loadFromFile("FunnelSans-VariableFont_wght.ttf")) {
        std::cout << "Font not found!\n";
        return 1;
    }

    Button btnNext("Next", {620, 520}, font);
    Button btnPrev("Previous", {40, 520}, font);
    Button btnDelete("Delete", {220, 520}, font);
    Button btnInsert("Insert", {420, 520}, font);

    sf::Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(20, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (btnNext.isClicked(mousePos)) viewer.nextImage();
                if (btnPrev.isClicked(mousePos)) viewer.prevImage();
                if (btnDelete.isClicked(mousePos)) viewer.deleteImage();
                if (btnInsert.isClicked(mousePos)) {
                    std::string path;
                    std::cout << "Enter image path: ";
                    std::getline(std::cin, path);
                    viewer.insertImage(path);
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        btnNext.updateHover(mousePos);
        btnPrev.updateHover(mousePos);
        btnDelete.updateHover(mousePos);
        btnInsert.updateHover(mousePos);

        window.clear(sf::Color(44, 62, 80));

        if (viewer.hasImage()) {
            window.draw(viewer.getSprite());
            statusText.setString("Viewing: " + viewer.getCurrentImageName());
        } else {
            statusText.setString("No image loaded. Click 'Insert' to add.");
        }

        window.draw(statusText);
        btnNext.draw(window);
        btnPrev.draw(window);
        btnDelete.draw(window);
        btnInsert.draw(window);

        window.display();
    }

    return 0;
}
