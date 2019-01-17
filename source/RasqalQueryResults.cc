#include <stdio.h>

#include "RasqalQueryResults.hh"

void RasqalQueryResults::loadBindingResults()
{
    if(m_results == NULL)
    {
        return;
    }

    while(!rasqal_query_results_finished(m_results))
    {
        int i;
        std::map<std::string, rasqal_literal *> bindingResults;

        for(i = 0; i < rasqal_query_results_get_bindings_count(m_results); i++)
        {
            const unsigned char *name = rasqal_query_results_get_binding_name(m_results, i);
            rasqal_literal *value = rasqal_query_results_get_binding_value(m_results, i);
            bindingResults[(const char *)name] = value;
        }

        m_bindingResults.push_back(bindingResults);
        rasqal_query_results_next(m_results);
    }

}

void RasqalQueryResults::printBindings()
{
    int count = 0;
    for(auto &bindingResult : m_bindingResults)
    {
        for(auto result: bindingResult)
        {
            printf("result %d: variable %s=", count+1,
                   result.first.c_str());
            rasqal_literal_print(result.second, stdout);
            putchar('\n');
        }
        printf("\n");
        count++;
    }
}
