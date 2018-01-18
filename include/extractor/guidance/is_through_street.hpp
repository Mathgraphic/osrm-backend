#ifndef OSRM_EXTRACTOR_GUIDANCE_IS_THROUGH_STREET_HPP_
#define OSRM_EXTRACTOR_GUIDANCE_IS_THROUGH_STREET_HPP_

#include "extractor/guidance/constants.hpp"
#include "extractor/guidance/mergable_road_detector.hpp"
#include "extractor/guidance/sliproad_handler.hpp"
#include "util/assert.hpp"
#include "util/bearing.hpp"
#include "util/coordinate_calculation.hpp"
#include "util/guidance/name_announcements.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits>

#include <boost/assert.hpp>

using osrm::extractor::guidance::getTurnDirection;
using osrm::util::angularDeviation;

namespace osrm
{
namespace extractor
{
namespace guidance
{

template <typename IntersectionType>
inline bool isThroughStreet(const std::size_t index,
                            const IntersectionType &intersection,
                            const util::NodeBasedDynamicGraph &node_based_graph,
                            const EdgeBasedNodeDataContainer &node_data_container,
                            const util::NameTable &name_table,
                            const SuffixTable &street_name_suffix_table)
{

    const auto &data_at_index = node_data_container.GetAnnotation(
        node_based_graph.GetEdgeData(intersection[index].eid).annotation_data);

    if (data_at_index.name_id == EMPTY_NAMEID)
        return false;

    // a through street cannot start at our own position -> index 1
    for (std::size_t road_index = 1; road_index < intersection.size(); ++road_index)
    {
        if (road_index == index)
            continue;

        const auto &road = intersection[road_index];
        const auto &road_data = node_data_container.GetAnnotation(
            node_based_graph.GetEdgeData(road.eid).annotation_data);

        // roads have a near straight angle (180 degree)
        const bool is_nearly_straight = angularDeviation(road.angle, intersection[index].angle) >
                                        (STRAIGHT_ANGLE - FUZZY_ANGLE_DIFFERENCE);

        const bool have_same_name = MergableRoadDetector::HaveIdenticalNames(
            data_at_index.name_id, road_data.name_id, name_table, street_name_suffix_table);

        const bool have_same_category =
            node_based_graph.GetEdgeData(intersection[index].eid).flags.road_classification ==
            node_based_graph.GetEdgeData(road.eid).flags.road_classification;

        if (is_nearly_straight && have_same_name && have_same_category)
            return true;
    }
    return false;
}

} // namespace guidance
} // namespace extractor
} // namespace osrm

#endif /*OSRM_EXTRACTOR_GUIDANCE_IS_THROUGH_STREET_HPP_*/