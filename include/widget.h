#ifndef WIDGET_H
#define WIDGET_H

struct Universe;

class Widget
{
public:
    void initialize();
    void resize(int width, int height);
    void draw(const Universe& universe) const;

    int width() const;
    int height() const;
};

#endif /* WIDGET_H */
