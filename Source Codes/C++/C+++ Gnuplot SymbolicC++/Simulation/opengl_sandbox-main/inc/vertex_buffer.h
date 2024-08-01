/*********************************************************************************************************************
 * File : vertex_buffer.h                                                                                            *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
public:
    // Set it to dynamic if we don't specify the data pointer
    VertexBuffer(unsigned int bytes_size, const void *data = nullptr);

    ~VertexBuffer();

    void bind() const;

    void unbind() const;

    void update_buffer(unsigned int bytes_size, const void *data);

private:
    unsigned int rendered_id_;
};

#endif // VERTEX_BUFFER_H
