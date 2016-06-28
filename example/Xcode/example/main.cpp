//
//  main.cpp
//  example
//
//  Created by Bryan on 6/23/16.
//  Copyright © 2016 SBOL Development Community. All rights reserved.
//

#include "sbol.h"
#include <iostream>

using namespace sbol;

int main() {
    Document& doc = *new Document();
    doc.read("../../../../../../CRISPR_example.xml");
    return 0;
}
