#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

template<class T1, class T2> bool isIntersecting(T1 &one, T2 &two)
{
    return one.right() >=  two.left() && one.left() <= two.right()
        && one.bottom() >= two.top() && one.top() <= two.bottom();
}

#endif // COLLISIONS_HPP
