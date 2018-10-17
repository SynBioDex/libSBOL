#ifndef RASQALQUERY_HH
#define RASQALQUERY_HH

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>

#include <rasqal/rasqal.h>
#include "SharedPtrWrapper.hh"

class RasqalQueryResults
{
public:
    typedef std::vector<std::map<std::string, rasqal_literal *>> BindingResults;

private:
    // Note the order is important here.  The objects will be deleted
    // in the opposite order they are listed.
    SharedPtrWrapper<rasqal_world> m_rasqalWorld;
    SharedPtrWrapper<rasqal_query> m_query;
    SharedPtrWrapper<rasqal_query_results> m_results;

    BindingResults m_bindingResults;

    void loadBindingResults();

public:

    RasqalQueryResults() {
    }

    RasqalQueryResults(SharedPtrWrapper<rasqal_world> rasqalWorld,
                       rasqal_query *query,
                       rasqal_query_results *results) : m_rasqalWorld(rasqalWorld),
                                                        m_query(query),
                                                        m_results(results) {
        m_rasqalWorld.setDeleter(rasqal_free_world);
        m_results.setDeleter(rasqal_free_query_results);
        m_query.setDeleter(rasqal_free_query);
        loadBindingResults();
    }

    RasqalQueryResults &operator=(const RasqalQueryResults &rhs) {
        m_bindingResults = rhs.m_bindingResults;

        // Note the order is important here.  The query can not be deleted
        // after the query results
        m_results = rhs.m_results;
        m_query = rhs.m_query;
        m_rasqalWorld = rhs.m_rasqalWorld;

        return *this;
    }

    rasqal_query_results *results() const {
        return m_results;
    }

    const BindingResults & bindingResults() const {
        return m_bindingResults;
    }


    rasqal_query_results_type type() const {
        if(m_results == NULL) {
            return RASQAL_QUERY_RESULTS_UNKNOWN;
        }

        return rasqal_query_results_get_type(m_results);
    }

    void printBindings();
};

#endif
