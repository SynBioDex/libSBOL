#include <iostream>
#include <stdexcept>

#include "RasqalDataGraph.hh"

RasqalDataGraph::RasqalDataGraph(const std::string &fName, raptor_uri *nameURI)
{
    m_rasqalWorld = rasqal_new_world();
    m_rasqalWorld.setDeleter(rasqal_free_world);
    if(m_rasqalWorld == NULL)
    {
        // Note this will cause rasqal_free_world() to be called
        m_rasqalWorld = NULL;
        throw std::runtime_error("rasqal_new_world() failed");
    }

    int res = rasqal_world_open(m_rasqalWorld);
    if(res != 0)
    {
        // Note this will cause rasqal_free_world() to be called
        m_rasqalWorld = NULL;
        throw std::runtime_error("Failed to open rasqal world");
    }

    const unsigned char *uri = NULL;
    uri = raptor_uri_filename_to_uri_string(fName.c_str());

    raptor_world *raptorWorld = rasqal_world_get_raptor(m_rasqalWorld);
    m_baseURI = raptor_new_uri(raptorWorld, uri);
    m_baseURI.setDeleter(raptor_free_uri);
    raptor_free_memory((void *)uri);

    m_dataGraph = rasqal_new_data_graph_from_uri(m_rasqalWorld,
                                                 /* source URI */ m_baseURI,
                                                 /* name URI */ NULL,
                                                 RASQAL_DATA_GRAPH_NAMED,
                                                 NULL, NULL, NULL);

    m_dataGraph.setDeleter(rasqal_free_data_graph);
    if(m_dataGraph == NULL)
    {
        // Note this will cause rasqal_free_world() to be called
        m_rasqalWorld = NULL;
        // Note this will cause rasqal_free_uri() to be called
        m_baseURI = NULL;
        throw std::runtime_error("Failed to create data graph");
    }
}

RasqalQueryResults RasqalDataGraph::query(const std::string &queryString) const
{
    rasqal_query *rasqalQuery =
        rasqal_new_query(m_rasqalWorld, "sparql", NULL);

    if(rasqalQuery == NULL)
    {
        throw std::runtime_error("rasqual_new_query() failed");
    }

    int res = rasqal_query_prepare(rasqalQuery,
                                   (const unsigned char *)queryString.c_str(),
                                   m_baseURI);
    if(res != 0)
    {
        rasqal_free_query(rasqalQuery);
        throw std::runtime_error("Failed to prepare query");
    }

    rasqal_data_graph *dg = rasqal_new_data_graph_from_data_graph(m_dataGraph);

    res = rasqal_query_add_data_graph(rasqalQuery, dg);
    if(res != 0)
    {
        rasqal_free_data_graph(dg);
        rasqal_free_query(rasqalQuery);
        throw std::runtime_error("Failed to add data graph to the query");
    }

    rasqal_query_results *results = rasqal_query_execute(rasqalQuery);

    if(results == NULL)
    {
        rasqal_free_data_graph(dg);
        rasqal_free_query(rasqalQuery);
        throw std::runtime_error("Query failed!");
    }

    return RasqalQueryResults(m_rasqalWorld, rasqalQuery, results);
}
