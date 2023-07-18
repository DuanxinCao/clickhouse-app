#include <iostream>
#include <memory>
#include <clickhouse/client.h>

using namespace clickhouse;

int main()
{
    /// Initialize client connection.
    Client client(ClientOptions().SetHost("localhost"));

    /// Create a table.
    client.Execute("CREATE TABLE IF NOT EXISTS default.numbers (id UInt64, name String) ENGINE = Memory");

    /// Insert some values.
    {
        Block block;

        auto id = std::make_shared<ColumnUInt64>();
        id->Append(1);
        id->Append(7);

        auto name = std::make_shared<ColumnString>();
        name->Append("one");
        name->Append("seven");

        block.AppendColumn("id"  , id);
        block.AppendColumn("name", name);

        client.Insert("default.numbers", block);
    }

//    std::shared_ptr<Block>block_ = nullptr;
//
//    /// Select values inserted in the previous step.
//    client.Select("SELECT id, name FROM default.numbers", [&](std::shared_ptr<Block> block) {
//        if(block_== nullptr || block_->GetRowCount()==0){
//            block_=block;
//        }
//        std::cout << "-----"<<block_->GetRowCount()<<std::endl;
//        for (size_t i = 0; i < block->GetRowCount(); ++i) {
//            std::cout << block->operator[](0)->As<ColumnUInt64>()->At(i) << " "
//                      << block->operator[](1)->As<ColumnString>()->At(i) << "\n";
//        }
//    });
//    std::cout << "+++"<<block_->GetRowCount()<<std::endl;
//    for (size_t i = 0; i < block_->GetRowCount(); ++i) {
//        std::cout << block_->operator[](0)->As<ColumnUInt64>()->At(i) << " "
//                  << block_->operator[](1)->As<ColumnString>()->At(i) << "\n";
//    }

    //    /// Select values inserted in the previous step.
//    client.Select("SELECT id, name FROM default.numbers", [] (std::shared_ptr<Block>block)
//        {
//            for (size_t i = 0; i < block->GetRowCount(); ++i) {
//                std::cout << block->operator[](0)->As<ColumnUInt64>()->At(i) << " "
//                          << block->operator[](1)->As<ColumnString>()->At(i) << "\n";
//            }
//        }
//    );

    /// Delete table.
    client.Execute("DROP TABLE default.numbers");

    return 0;
}
