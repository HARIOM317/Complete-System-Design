@REM Compile

g++ -o zepto_app main.cpp src/models/Cart.cpp src/models/Order.cpp src/models/Product.cpp src/models/User.cpp src/factories/ProductFactory.cpp src/services/DarkStore.cpp src/services/DbInventoryStore.cpp src/managers/DarkStoreManager.cpp src/managers/InventoryManager.cpp src/managers/OrderManager.cpp src/strategies/Strategies.cpp src/utils/ZeptoHelper.cpp -I include

@REM Run
.\zepto_app.exe  
