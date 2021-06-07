#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

#define Array(T) T*

void* initialize_array(size_t elem_size, size_t init_cap);

size_t get_array_length(Array(void) arr);

size_t get_array_capacity(Array(void) arr);

void expand_array(void** blockptr, size_t cur_cap, size_t cap);

void clear_array_data(void** blockptr);

void free_array(Array(void) arr);

static inline bool is_array_full(Array(void) arr)
{
    return get_array_length(arr) >= get_array_capacity(arr);
}

#define init_array(type, cap) (initialize_array(sizeof(type), cap))

#define try_to_expand(arr, cur_cap)                                                                                    \
    expand_array(((void**)&arr), (cur_cap * 2) * sizeof(*(arr)) + (sizeof(size_t) * 2), cur_cap * 2)

#define add_array_item(arr, item)                                                                                      \
    arr[get_array_length(arr)] = (item);                                                                               \
    ++((size_t*)(arr))[-1]

#define add_array(arr, item)                                                                                           \
    {                                                                                                                  \
        if (arr)                                                                                                       \
        {                                                                                                              \
            if (is_array_full(arr))                                                                                    \
            {                                                                                                          \
                try_to_expand(arr, get_array_capacity(arr));                                                           \
            }                                                                                                          \
            add_array_item(arr, item);                                                                                 \
        }                                                                                                              \
    }

#define add_range_array(dist, src, range)                                                                              \
    {                                                                                                                  \
        for (size_t i = 0; i < range; ++i)                                                                             \
        {                                                                                                              \
            add_array(dist, src[i]);                                                                                   \
        }                                                                                                              \
    }

#define search_array(arr, item, result)                                                                                \
    {                                                                                                                  \
        int left = 0, right = get_array_length(arr) - 1;                                                               \
        result = -1;                                                                                                   \
        while (left <= right)                                                                                          \
        {                                                                                                              \
            int mid = (int)(((unsigned)left + (unsigned)right) >> 1);                                                  \
            if (arr[mid] == item)                                                                                      \
            {                                                                                                          \
                result = mid;                                                                                          \
                break;                                                                                                 \
            }                                                                                                          \
            arr[mid] < item ? (left = mid + 1) : (right = mid - 1);                                                    \
        }                                                                                                              \
    }

#define clear_array(arr) clear_array_data((void**)&arr)

#define remove_array(arr, index)                                                                                       \
    {                                                                                                                  \
        if (index < get_array_length(arr))                                                                             \
        {                                                                                                              \
            for (size_t i = index; i < get_array_length(arr) - 1; ++i)                                                 \
            {                                                                                                          \
                arr[i] = arr[i + 1];                                                                                   \
            }                                                                                                          \
            --((size_t*)(arr))[-1];                                                                                    \
        }                                                                                                              \
    }

#endif