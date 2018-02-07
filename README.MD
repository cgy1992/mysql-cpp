# MYSQL-CPP

mysql-cpp is a wrapper of mysql c api for c++

# Usage
```cpp
#include <iostream>

#include <connection.h>
#include <driver.h>
#include <statement.h>
#include <resultset.h>

using namespace std;

int main()
{
    auto driver = Driver::get_instance();
    auto con = driver->connect("127.0.0.1", "root", "root", "test");
    try
    {
        auto stmt = con->prepareStatement("select col1, col2 from table;");
        auto result = stmt->execute();
        while (result->next())
        {
            auto col1 = result->getInt(0);
            auto col2 = result->getString(1);
  
            cout << col1 << col2 << endl;
        }
        
        auto stmt2 = con->prepareStatement("select col1 from table where col2=? and col3=?;");
        stmt2->setParam(0, 1);
        stmt2->setParam(1, "param2");
        
        /*
         * or
         * stmt2->setParams(100, "param2");
         */
         
        auto result2 = stmt2->execute();
        // fetch result...
        
    } catch (SQLException &e)
    {
        cout << e.what();
    }
    delete con;  // do not forget to delete connection
}
```

# Notice
`Driver::connect` is not thread safe, use mutex or whatever you like in multi-thread.
