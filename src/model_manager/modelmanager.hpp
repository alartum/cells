#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP

#include <map>
#include <model/model.hpp>
#include <string>

class ModelManager
{
public:
    ModelManager();
    std::shared_ptr<const Model> getModel(int typeID) const;
    void loadModel(int typeID, const std::shared_ptr<const Model>& model_ptr);
    void initSample();
private:
    // Models with ID
    std::map<int, std::shared_ptr<const Model> > mModels;
};

#endif // MODELMANAGER_HPP
