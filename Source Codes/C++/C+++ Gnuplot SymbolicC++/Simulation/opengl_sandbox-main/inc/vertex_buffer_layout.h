/*********************************************************************************************************************
 * File : vertex_buffer_layout.h                                                                                     *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type);
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();

    ~VertexBufferLayout();

    template <typename T>
    void push(unsigned int count);

    inline const std::vector<VertexBufferElement> &get_elements() const { return elements_; }

    inline unsigned int get_stride() const { return stride_; }

private:
    std::vector<VertexBufferElement> elements_;
    unsigned int stride_;
};

#endif // VERTEX_BUFFER_LAYOUT_H
