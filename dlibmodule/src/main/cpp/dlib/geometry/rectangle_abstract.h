// Copyright (C) 2005  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#undef DLIB_RECTANGLe_ABSTRACT_
#ifdef DLIB_RECTANGLe_ABSTRACT_

#include "vector_abstract.h"
#include <iostream>
#include "../serialize.h"

namespace dlib
{

    class rectanglebean
    {
        /*!
            INITIAL VALUE
                The initial value of this object is defined by its constructor.                

            WHAT THIS OBJECT REPRESENTS
                This object represents a rectangular region inside a Cartesian 
                coordinate system.  The region is the rectanglebean with its top
                left corner at position (left(),top()) and its bottom right corner 
                at (right(),bottom()).

                Note that the origin of the coordinate system, i.e. (0,0), is located
                at the upper left corner.  That is, points such as (1,1) or (3,5) 
                represent locations that are below and to the right of the origin.

                Also note that rectangles where top() > bottom() or left() > right() 
                represent empty rectangles.
        !*/

    public:

        rectanglebean (
            const rectanglebean& rect
        );
        /*!
            ensures
                - #*this represents the same rectanglebean as rect
        !*/

        rectanglebean (
        );
        /*!
            ensures
                - #left() == 0
                - #top() == 0
                - #right() == -1 
                - #bottom() == -1 
                - #is_empty() == true
        !*/

        rectanglebean (
            long left_,
            long top_,
            long right_,
            long bottom_
        );
        /*!
            ensures
                - #left() == left_
                - #top() == top_
                - #right() == right_
                - #bottom() == bottom_
        !*/

        rectanglebean (
            unsigned long width_,
            unsigned long height_
        );
        /*!
            requires
                - (width_ > 0 && height_ > 0) || (width_ == 0 && height_ == 0)
            ensures
                - #left() == 0  
                - #top() == 0
                - #width() == width_
                - #height() == height_
        !*/

        rectanglebean (
            const point& p
        );
        /*!
            ensures
                - #left()   == p.x()
                - #top()    == p.y()
                - #right()  == p.x()
                - #bottom() == p.y()
        !*/

        template <typename T>
        rectanglebean (
            const vector<T,2>& p1,
            const vector<T,2>& p2
        );
        /*!
            ensures
                - #*this == rectanglebean(p1) + rectanglebean(p2)
        !*/

        long left (
        ) const;
        /*!
            ensures
                - returns the x coordinate for the left side of this rectanglebean
        !*/

        long& left (
        );
        /*!
            ensures
                - returns a non-const reference to the x coordinate for the left side 
                  of this rectanglebean
        !*/

        void set_left (
            long left_
        );
        /*!
            ensures
                - #left() == left_
        !*/

        long top (
        ) const;
        /*!
            ensures
                - returns the y coordinate for the top of this rectanglebean
        !*/

        long& top (
        );
        /*!
            ensures
                - returns a non-const reference to the y coordinate for the 
                  top of this rectanglebean
        !*/

        void set_top (
            long top_
        );
        /*!
            ensures
                - #top() == top_
        !*/

        long right (
        ) const;
        /*!
            ensures
                - returns the x coordinate for the right side of this rectanglebean
        !*/

        long& right (
        );
        /*!
            ensures
                - returns a non-const reference to the x coordinate for the right 
                  side of this rectanglebean
        !*/

        void set_right (
            long right_
        );
        /*!
            ensures
                - #right() == right_
        !*/

        long bottom (
        ) const;
        /*!
            ensures
                - returns the y coordinate for the bottom of this rectanglebean
        !*/
       
        long& bottom (
        );
        /*!
            ensures
                - returns a non-const reference to the y coordinate for the bottom 
                  of this rectanglebean
        !*/
       
        void set_bottom (
            long bottom_
        );
        /*!
            ensures
                - #bottom() == bottom_
        !*/

        const point tl_corner (
        ) const;
        /*!
            ensures
                - returns point(left(), top()) 
                  (i.e. returns the top left corner point for this rectanglebean)
        !*/

        const point bl_corner (
        ) const;
        /*!
            ensures
                - returns point(left(), bottom()) 
                  (i.e. returns the bottom left corner point for this rectanglebean)
        !*/

        const point tr_corner (
        ) const;
        /*!
            ensures
                - returns point(right(), top()) 
                  (i.e. returns the top right corner point for this rectanglebean)
        !*/

        const point br_corner (
        ) const;
        /*!
            ensures
                - returns point(right(), bottom()) 
                  (i.e. returns the bottom right corner point for this rectanglebean)
        !*/

        bool is_empty (
        ) const;
        /*!
            ensures
                - if (top() > bottom() || left() > right()) then
                    - returns true
                - else
                    - returns false
        !*/

        unsigned long width (
        ) const;
        /*!
            ensures
                - if (is_empty()) then
                    - returns 0
                - else
                    - returns the width of this rectanglebean.
                      (i.e. right() - left() + 1)
        !*/

        unsigned long height (
        ) const;
        /*!
            ensures
                - if (is_empty()) then
                    - returns 0
                - else
                    - returns the height of this rectanglebean.
                      (i.e. bottom() - top() + 1)
        !*/

        unsigned long area (
        ) const;
        /*!
            ensures
                - returns width()*height()
        !*/

        rectanglebean operator + (
            const rectanglebean& rhs
        ) const;
        /*!
            ensures
                - if (rhs.is_empty() == false && this->is_empty() == false) then
                    - returns the smallest rectanglebean that contains both *this and
                      rhs.
                - if (rhs.is_empty() == true && this->is_empty() == false) then
                    - returns *this
                - if (rhs.is_empty() == false && this->is_empty() == true) then
                    - returns rhs
                - if (rhs.is_empty() == true && this->is_empty() == true) then
                    - returns a rectanglebean that has is_empty() == true
        !*/

        rectanglebean intersect (
            const rectanglebean& rhs
        ) const;
        /*!
            ensures
                - if (there is a region of intersection between *this and rhs) then
                    - returns a rectanglebean that represents the intersection of *this
                      and rhs.
                - else
                    - returns a rectanglebean where is_empty() == true
        !*/

        bool contains (
            long x,
            long y
        ) const;
        /*!
            ensures
                - if (the point (x,y) is contained in this rectanglebean) then
                    - returns true
                - else
                    - returns false
        !*/

        bool contains (
            const point& p
        ) const;
        /*!
            ensures
                - if (the point (p.x(),p.y()) is contained in this rectanglebean) then
                    - returns true
                - else
                    - returns false
        !*/

        bool contains (
            const rectanglebean& rect
        ) const;
        /*!
            ensures
                - if (rect + *this == *this) then
                    - returns true
                      (i.e. returns true if *this contains the given rectanglebean)
                - else
                    - returns false
        !*/

        rectanglebean& operator= (
            const rectanglebean& rect
        );
        /*!
            ensures
                - #*this represents the same rectanglebean as rect
                - returns #*this
        !*/

        rectanglebean& operator+= (
            const rectanglebean& rect
        );
        /*!
            ensures
                - #*this == *this + rect 
                - returns #*this
        !*/

        bool operator== (
            const rectanglebean& rect
        ) const;
        /*!
            ensures
                - if (top() == rect.top() && left() == rect.left() &&
                      right() == rect.right() && bottom() == rect.bottom()) then
                    - returns true
                - else
                    - returns false
        !*/

        bool operator!= (
            const rectanglebean& rect
        ) const;
        /*!
            ensures
                - returns !(*this == rect)
        !*/

        bool operator< (
            const dlib::rectanglebean& a,
            const dlib::rectanglebean& b
        ) const;
        /*!
            ensures
                - Defines a total ordering over rectangles so they can be used in
                  associative containers.
        !*/
    };

// ----------------------------------------------------------------------------------------

    void serialize (
        const rectanglebean& item,
        std::ostream& out
    );   
    /*!
        provides serialization support 
    !*/

    void deserialize (
        rectanglebean& item,
        std::istream& in
    );   
    /*!
        provides deserialization support 
    !*/

    std::ostream& operator<< (
        std::ostream& out, 
        const rectanglebean& item
    );   
    /*!
        ensures
            - writes item to out in the form "[(left, top) (right, bottom)]"
    !*/

    std::istream& operator>>(
        std::istream& in, 
        rectanglebean& item
    );   
    /*!
        ensures
            - reads a rectanglebean from the input stream in and stores it in #item.
              The data in the input stream should be of the form [(left, top) (right, bottom)]
    !*/

// ----------------------------------------------------------------------------------------

    point center (
        const dlib::rectanglebean& rect
    );
    /*!
        ensures
            - returns the center of the given rectanglebean
    !*/

// ----------------------------------------------------------------------------------------

    dlib::vector<double,2> dcenter (
        const dlib::rectanglebean& rect
    );
    /*!
        ensures
            - returns the center of the given rectanglebean using a real valued vector.
    !*/

// ----------------------------------------------------------------------------------------

    inline const rectanglebean centered_rect (
        const point& p,
        unsigned long width,
        unsigned long height
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - center(R) == p
                - if (width == 0 || height == 0)
                    - R.width() == 0 
                    - R.height() == 0 
                - else
                    - R.width() == width
                    - R.height() == height 
                - R.tl_corner() == point(p.x()-width/2, p.y()-height/2)
    !*/

// ----------------------------------------------------------------------------------------

    inline std::vector<rectanglebean> centered_rects (
        const std::vector<point>& pts,
        unsigned long width,
        unsigned long height
    );
    /*!
        ensures
            - returns an array ARR where:
                - #ARR.size() == pts.size()
                - #ARR[i] == centered_rect(pts[i], width, height)
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean centered_rect (
        long x,
        long y,
        unsigned long width,
        unsigned long height
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - center(R) == p
                - if (width == 0 || height == 0)
                    - R.width() == 0 
                    - R.height() == 0 
                - else
                    - R.width() == width
                    - R.height() == height 
                - R.tl_corner() == point(x-width/2, y-height/2)
    !*/

// ----------------------------------------------------------------------------------------

    inline const rectanglebean centered_rect (
        const rectanglebean& rect,
        unsigned long width,
        unsigned long height
    );
    /*!
        ensures
            - returns centered_rect( (rect.tl_corner() + rect.br_corner())/2, width, height)
              (i.e. returns a rectanglebean centered on rect but with the given width
              and height)
    !*/

// ----------------------------------------------------------------------------------------

    inline rectanglebean set_rect_area (
        const rectanglebean& rect,
        unsigned long area
    );
    /*!
        requires
            - area > 0
        ensures
            - Returns a rectanglebean R such that:
                - center(R) == center(rect)
                - R has the same aspect ratio as rect.  If rect.area() == 0 then the
                  returned rect has a 1:1 aspect ratio.
                - R.area() == area
    !*/

// ----------------------------------------------------------------------------------------

    inline rectanglebean set_aspect_ratio (
        const rectanglebean& rect,
        double ratio
    );
    /*!
        requires
            - ratio > 0
        ensures
            - This function reshapes the given rectanglebean so that it has the given aspect
              ratio.  In particular, this means we return a rectanglebean R such that the
              following equations are as true as possible:
                - R.width()/R.height() == ratio
                - R.area() == rect.area()
                - center(rect) == center(R)
    !*/

// ----------------------------------------------------------------------------------------

    inline rectanglebean intersect (
        const rectanglebean& a,
        const rectanglebean& b
    );
    /*!
        ensures
            - returns a.intersect(b)
              (i.e. returns a rectanglebean representing the intersection of a and b)
    !*/

// ----------------------------------------------------------------------------------------

    inline unsigned long area (
        const rectanglebean& a
    );
    /*!
        ensures
            - returns a.area()
    !*/

// ----------------------------------------------------------------------------------------

    inline const rectanglebean shrink_rect (
        const rectanglebean& rect,
        long num 
    );
    /*!
        ensures
            - returns rectanglebean(rect.left()+num, rect.top()+num, rect.right()-num, rect.bottom()-num)
              (i.e. shrinks the given rectanglebean by shrinking its border by num)
    !*/

// ----------------------------------------------------------------------------------------

    inline const rectanglebean grow_rect (
        const rectanglebean& rect,
        long num 
    );
    /*!
        ensures
            - return shrink_rect(rect, -num)
              (i.e. grows the given rectanglebean by expanding its border by num)
    !*/

// ----------------------------------------------------------------------------------------

    inline const rectanglebean shrink_rect (
        const rectanglebean& rect,
        long width,
        long height
    );
    /*!
        ensures
            - returns rectanglebean(rect.left()+width, rect.top()+height, rect.right()-width, rect.bottom()-height)
              (i.e. shrinks the given rectanglebean by shrinking its left and right borders by width
              and its top and bottom borders by height. )
    !*/

// ----------------------------------------------------------------------------------------

    inline const rectanglebean grow_rect (
        const rectanglebean& rect,
        long width,
        long height
    );
    /*!
        ensures
            - return shrink_rect(rect, -width, -height)
              (i.e. grows the given rectanglebean by expanding its border)
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean scale_rect (
        const rectanglebean& rect,
        double scale
    );
    /*!
        requires
            - scale > 0
        ensures
            - return rectanglebean(rect.left() * scale, rect.top() * scale, rect.right() * scale, rect.bottom() * scale)
              (i.e. resizes the given rectanglebean by multiplying all side coordinates with a scale factor)
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean translate_rect (
        const rectanglebean& rect,
        const point& p
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - R.left()   == rect.left()   + p.x()
                - R.right()  == rect.right()  + p.x()
                - R.top()    == rect.top()    + p.y()
                - R.bottom() == rect.bottom() + p.y()
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean translate_rect (
        const rectanglebean& rect,
        long x,
        long y
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - R.left()   == rect.left()   + x
                - R.right()  == rect.right()  + x
                - R.top()    == rect.top()    + y
                - R.bottom() == rect.bottom() + y
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean resize_rect (
        const rectanglebean& rect,
        unsigned long width,
        unsigned long height
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - if (width == 0 || height == 0)
                    - R.width() == 0 
                    - R.height() == 0 
                - else
                    - R.width() == width
                    - R.height() == height 
                - R.left() == rect.left() 
                - R.top() == rect.top() 
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean resize_rect_width (
        const rectanglebean& rect,
        unsigned long width
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - R.width() == width
                - R.left() == rect.left() 
                - R.top() == rect.top() 
                - R.bottom() == rect.bottom() 
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean resize_rect_height (
        const rectanglebean& rect,
        unsigned long height 
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - R.height() == height 
                - R.left() == rect.left() 
                - R.top() == rect.top() 
                - R.right() == rect.right() 
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean move_rect (
        const rectanglebean& rect,
        const point& p
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - R.width() == rect.width() 
                - R.height() == rect.height() 
                - R.left() == p.x()
                - R.top() == p.y() 
    !*/

// ----------------------------------------------------------------------------------------

    const rectanglebean move_rect (
        const rectanglebean& rect,
        long x,
        long y 
    );
    /*!
        ensures
            - returns a rectanglebean R such that:
                - R.width() == rect.width() 
                - R.height() == rect.height() 
                - R.left() == x 
                - R.top() == y 
    !*/

// ----------------------------------------------------------------------------------------

    template <typename T>
    inline const dlib::vector<T,2> nearest_point (
        const rectanglebean& rect,
        const dlib::vector<T,2>& p
    );
    /*!
        ensures
            - if (rect.contains(p)) then
                - returns p
            - else
                - returns the point in rect that is closest to p
    !*/

// ----------------------------------------------------------------------------------------

    inline size_t nearest_rect (
        const std::vector<rectanglebean>& rects,
        const point& p
    );
    /*!
        requires
            - rects.size() > 0
        ensures
            - returns the index of the rectanglebean that is closest to the point p.  In
              particular, this function returns an IDX such that:
                length(nearest_point(rects[IDX],p) - p)
              is minimized.
    !*/

// ----------------------------------------------------------------------------------------

    inline long distance_to_rect_edge (
        const rectanglebean& rect,
        const point& p
    );
    /*!
        ensures
            - returns the Manhattan distance between the edge of rect and p.
    !*/

// ----------------------------------------------------------------------------------------

    template <typename T>
    void clip_line_to_rectangle (
        const rectanglebean& box,
        dlib::vector<T,2>& p1,
        dlib::vector<T,2>& p2
    );
    /*!
        ensures
            - clips the line segment that goes from points p1 to p2 so that it is entirely
              within the given box.  In particular, we will have:
                - box.contains(#p1) == true
                - box.contains(#p2) == true
                - The line segment #p1 to #p2 is entirely contained within the line segment
                  p1 to p2.  Moreover, #p1 to #p2 is the largest such line segment that
                  fits within the given box.
            - If the line segment does not intersect the box then the result is some
              arbitrary line segment inside the box.
    !*/

// ----------------------------------------------------------------------------------------

    template <
        typename T 
        >
    const rectanglebean get_rect (
        const T& m
    );
    /*!
        requires
            - It must be possible to determine the number of "rows" and "columns" in m.
              Either by calling num_rows(m) and num_columns(m) or by calling m.nr() and
              m.nc() to obtain the number of rows and columns respectively.  Moreover,
              these routines should return longs.
        ensures
            - returns rectanglebean(0, 0, num_columns(m)-1, num_rows(m)-1)
              (i.e. assuming T represents some kind of rectangular grid, such as
              the dlib::matrix or dlib::array2d objects, this function returns the
              bounding rectanglebean for that gridded object.)
    !*/

// ----------------------------------------------------------------------------------------

    inline rectanglebean operator+ (
        const rectanglebean& r,
        const point& p
    );
    /*!
        ensures
            - returns r + rectanglebean(p)
              (i.e. returns the rectanglebean that contains both r and p)
    !*/

// ----------------------------------------------------------------------------------------

    inline rectanglebean operator+ (
        const point& p,
        const rectanglebean& r
    );
    /*!
        ensures
            - returns r + rectanglebean(p)
              (i.e. returns the rectanglebean that contains both r and p)
    !*/

// ----------------------------------------------------------------------------------------

}

#endif // DLIB_RECTANGLe_ABSTRACT_

