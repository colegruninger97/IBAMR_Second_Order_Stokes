// ---------------------------------------------------------------------
//
// Copyright (c) 2007 - 2019 by the IBAMR developers
// All rights reserved.
//
// This file is part of IBAMR.
//
// IBAMR is free software and is distributed under the 3-clause BSD
// license. The full text of the license can be found in the file
// COPYRIGHT at the top level directory of IBAMR.
//
// ---------------------------------------------------------------------

/////////////////////////////// INCLUDE GUARD ////////////////////////////////

#ifndef included_IBAMR_IBBeamForceSpec
#define included_IBAMR_IBBeamForceSpec

/////////////////////////////// INCLUDES /////////////////////////////////////

#include <ibamr/config.h>

#include "ibtk/Streamable.h"
#include "ibtk/StreamableFactory.h"
#include "ibtk/ibtk_utilities.h"

#include "tbox/Pointer.h"

#include <utility>
#include <vector>

namespace SAMRAI
{
namespace hier
{
template <int DIM>
class IntVector;
} // namespace hier
namespace tbox
{
class AbstractStream;
} // namespace tbox
} // namespace SAMRAI

/////////////////////////////// CLASS DEFINITION /////////////////////////////

namespace IBAMR
{
/*!
 * \brief Class IBBeamForceSpec encapsulates the data necessary to compute the
 * forces generated by a collection of linear beams (i.e., structures that
 * resist bending) at a single node of the Lagrangian mesh.
 *
 * Beams are connections between three particular nodes of the Lagrangian mesh.
 * IBBeamForceSpec objects are stored as IBTK::Streamable data associated with
 * only the master beam nodes in the mesh.
 */
class IBBeamForceSpec : public IBTK::Streamable
{
public:
    /*!
     * \note This typedef appears to be needed to get g++ to parse the default
     * parameters in the class constructor.
     */
    using NeighborIdxs = std::pair<int, int>;

    /*!
     * \brief Register this class and its factory class with the singleton
     * IBTK::StreamableManager object.  This method must be called before any
     * IBBeamForceSpec objects are created.
     *
     * \note This method is collective on all MPI processes.  This is done to
     * ensure that all processes employ the same class ID for the
     * IBBeamForceSpec class.
     */
    static void registerWithStreamableManager();

    /*!
     * \brief Returns a boolean indicating whether the class has been registered
     * with the singleton IBTK::StreamableManager object.
     */
    static bool getIsRegisteredWithStreamableManager();

    /*!
     * The unique class ID for this object type assigned by the
     * IBTK::StreamableManager.
     */
    static int STREAMABLE_CLASS_ID;

    /*!
     * \brief Default constructor.
     */
    IBBeamForceSpec(unsigned int num_beams = 0);

    /*!
     * \brief Alternative constructor.
     */
    IBBeamForceSpec(int master_idx,
                    const std::vector<NeighborIdxs>& neighbor_idxs,
                    const std::vector<double>& bend_rigidities,
                    const std::vector<IBTK::Vector>& mesh_dependent_curvatures);

    /*!
     * \brief Destructor.
     */
    ~IBBeamForceSpec();

    /*!
     * \return The number of beams attached to the master node.
     */
    unsigned int getNumberOfBeams() const;

    /*!
     * \return A const reference to the master node index.
     */
    const int& getMasterNodeIndex() const;

    /*!
     * \return A non-const reference to the master node index.
     */
    int& getMasterNodeIndex();

    /*!
     * \return A const reference to the neighbor node indices for the beams
     * attached to the master node.
     */
    const std::vector<NeighborIdxs>& getNeighborNodeIndices() const;

    /*!
     * \return A non-const reference to the neighbor node indices for the beams
     * attached to the master node.
     */
    std::vector<NeighborIdxs>& getNeighborNodeIndices();

    /*!
     * \return A const reference to the bending rigidities of the beams attached
     * to the master node.
     */
    const std::vector<double>& getBendingRigidities() const;

    /*!
     * \return A non-const reference to the bending rigidities of the beams
     * attached to the master node.
     */
    std::vector<double>& getBendingRigidities();

    /*!
     * \return A const reference to the mesh-dependent curvatures of the beams
     * attached to the master node.
     */
    const std::vector<IBTK::Vector>& getMeshDependentCurvatures() const;

    /*!
     * \return A non-const reference to the mesh-dependent curvatures of the
     * beams attached to the master node.
     */
    std::vector<IBTK::Vector>& getMeshDependentCurvatures();

    /*!
     * \brief Return the unique identifier used to specify the
     * IBTK::StreamableFactory object used by the IBTK::StreamableManager to
     * extract Streamable objects from data streams.
     */
    int getStreamableClassID() const override;

    /*!
     * \brief Return an upper bound on the amount of space required to pack the
     * object to a buffer.
     */
    size_t getDataStreamSize() const override;

    /*!
     * \brief Pack data into the output stream.
     */
    void packStream(SAMRAI::tbox::AbstractStream& stream) override;

private:
    /*!
     * \brief Copy constructor.
     *
     * \note This constructor is not implemented and should not be used.
     *
     * \param from The value to copy to this object.
     */
    IBBeamForceSpec(const IBBeamForceSpec& from) = delete;

    /*!
     * \brief Assignment operator.
     *
     * \note This operator is not implemented and should not be used.
     *
     * \param that The value to assign to this object.
     *
     * \return A reference to this object.
     */
    IBBeamForceSpec& operator=(const IBBeamForceSpec& that) = delete;

    /*!
     * Data required to compute the beam forces.
     */
    int d_master_idx = IBTK::invalid_index;
    std::vector<NeighborIdxs> d_neighbor_idxs;
    std::vector<double> d_bend_rigidities;
    std::vector<IBTK::Vector> d_mesh_dependent_curvatures;

    /*!
     * \brief A factory class to rebuild IBBeamForceSpec objects from
     * SAMRAI::tbox::AbstractStream data streams.
     */
    class Factory : public IBTK::StreamableFactory
    {
    public:
        /*!
         * \brief Destructor.
         */
        ~Factory() = default;

        /*!
         * \brief Return the unique identifier used to specify the
         * IBTK::StreamableFactory object used by the IBTK::StreamableManager to
         * extract IBBeamForceSpec objects from data streams.
         */
        int getStreamableClassID() const override;

        /*!
         * \brief Set the unique identifier used to specify the
         * IBTK::StreamableFactory object used by the IBTK::StreamableManager to
         * extract IBBeamForceSpec objects from data streams.
         */
        void setStreamableClassID(int class_id) override;

        /*!
         * \brief Build an IBBeamForceSpec object by unpacking data from the
         * data stream.
         */
        SAMRAI::tbox::Pointer<IBTK::Streamable> unpackStream(SAMRAI::tbox::AbstractStream& stream,
                                                             const SAMRAI::hier::IntVector<NDIM>& offset) override;

    private:
        /*!
         * \brief Default constructor.
         */
        Factory();

        /*!
         * \brief Copy constructor.
         *
         * \note This constructor is not implemented and should not be used.
         *
         * \param from The value to copy to this object.
         */
        Factory(const Factory& from) = delete;

        /*!
         * \brief Assignment operator.
         *
         * \note This operator is not implemented and should not be used.
         *
         * \param that The value to assign to this object.
         *
         * \return A reference to this object.
         */
        Factory& operator=(const Factory& that) = delete;

        friend class IBBeamForceSpec;
    };
    using IBBeamForceSpecFactory = IBBeamForceSpec::Factory;
};
} // namespace IBAMR

/////////////////////////////// INLINE ///////////////////////////////////////

#include "ibamr/private/IBBeamForceSpec-inl.h" // IWYU pragma: keep

//////////////////////////////////////////////////////////////////////////////

#endif //#ifndef included_IBAMR_IBBeamForceSpec
