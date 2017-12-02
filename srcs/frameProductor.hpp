
#ifndef __FRAME_PRODUCTOR_HPP__
# define __FRAME_PRODUCTOR_HPP__

#include <iostream>
#include <thread>
#include "renderer/renderedFrame.hpp"
#include "renderer/renderer.hpp"
#include "physician/physician.hpp"
#include "math/polynom.hpp"
#include "utils/pool.hpp"

/*
 *                    grid_u, grid_v
 *           pressurer              graviter
 *                        physician
*/

/*
 * Some explications about auo amd new int[x][y][z] on the heap,
 * https://stackoverflow.com/questions/17258749/is-there-a-way-of-casting-a-pointer-to-an-array-type
 * https://www.reddit.com/r/cpp/comments/6ge86r/auto_for_in_class_initialization_of_nonstatic/
 * http://en.cppreference.com/w/cpp/types/decay
*/

/*
 *      the MAC grid
 *
 *          y, j, v
 *          |
 *          |
 *          |
 *          |
 *          |---------------- x, i, u
 *          /
 *         /
 *        /
 *       /
 *      z, k, w
 *
 *      p(i,j,k) = pi,j,k,
 *      u(i,j,k) = ui−1/2,j,k
 *      v(i,j,k) = vi,j−1/2,k
 *      w(i,j,k) = wi,j,k−1/2
 *
 * in 2 dimensions:
 *
 *                         v(i, j + 1/2) <=> v(i, j + 1)
 *                           ^
 *                    _______|_______
 *                    |             |
 *                    |             |
 *  u(i - 1/2, j)   <-|  p(i,j)     |-> u(i + 1/2, j) <=> v(i + 1, j)
 *  <=> u(i - 1/2, j) |             |
 *                    |             |
 *                    ---------------
 *                           |
 *                         v(i, j - 1/2) <=> v(i, j)
 *
*/

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

namespace mod1
{
class FrameProductor
{
public:
    FrameProductor(const std::shared_ptr<std::Pool<RenderedFrame>> &pool);
    ~FrameProductor();
    void start();
    void stop();
//    bool parseFile(const char &buff);
    bool parseFile();

private:
    void threadHandler();
    void raytrace(RenderedFrame *img);

    const std::shared_ptr<std::Pool<RenderedFrame>> m_pool;
    bool m_keepGoing = false;
    auto_init(m_grid, new struct cell[MATH_WIDTH][MATH_HEIGHT]);
    auto_init(m_particles, new struct particle[NB_PARTICLES]);
    Polynom m_groundLevel;
    std::unique_ptr<Renderer> m_renderer = nullptr;
    std::unique_ptr<Physician> m_physician = nullptr;
};
}

#endif
