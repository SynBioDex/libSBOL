#ifndef RASQALDATAGRAPH_CC
#define RASQALDATAGRAPH_CC

#include <string>

#include <rasqal/rasqal.h>
#include <raptor2/raptor2.h>

#include "SharedPtrWrapper.hh"
#include "RasqalQueryResults.hh"

class RasqalDataGraph
{
    // Note the order is important here.  The objects will be deleted
    // in the opposite order they are listed.
    SharedPtrWrapper<rasqal_world> m_rasqalWorld;
    SharedPtrWrapper<raptor_uri> m_baseURI;
    SharedPtrWrapper<rasqal_data_graph> m_dataGraph;

public:
    RasqalDataGraph(const std::string &fName, raptor_uri *nameURI = NULL);
    RasqalDataGraph() {};

    RasqalDataGraph(const RasqalDataGraph &src) : m_rasqalWorld(src.m_rasqalWorld) {
        m_dataGraph = rasqal_new_data_graph_from_data_graph(src.m_dataGraph);
        m_baseURI = raptor_uri_copy(src.m_baseURI);
    }

    RasqalDataGraph &operator=(const RasqalDataGraph &rhs) {
        // m_dataGraph and m_baseURI are copied, and m_rasqalWorld is shared
        m_dataGraph = rasqal_new_data_graph_from_data_graph(rhs.m_dataGraph);
        m_baseURI = raptor_uri_copy(rhs.m_baseURI);
        m_rasqalWorld = rhs.m_rasqalWorld;

        return *this;
    }

    rasqal_world *rasqalWorld() const {
        return m_rasqalWorld;
    }

    raptor_world *raptorWorld() const {
        return rasqal_world_get_raptor(m_rasqalWorld);
    }

    rasqal_data_graph *dataGraph() const {
        return m_dataGraph;
    }

    RasqalQueryResults query(const std::string &queryString) const;
};

#endif
