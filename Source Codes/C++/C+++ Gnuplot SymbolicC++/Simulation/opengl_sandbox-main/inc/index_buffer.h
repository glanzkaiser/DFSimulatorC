/*********************************************************************************************************************
 * File : vertex_buffer.h                                                                                            *
 *                                                                                                                   *
 * 2020 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int *data, unsigned int count);

    ~IndexBuffer();

    void bind() const;

    void unbind() const;

    inline unsigned int get_count() const { return count_; }

private:
    unsigned int rendered_id_;
    unsigned int count_; ///< Number of indices
};

#endif // INDEX_BUFFER_H
