#ifndef CRESOURCE_MANAGER_HPP_
#define CRESOURCE_MANAGER_HPP_

#include <map>

template<typename Enum, typename Resource>

class CResourceManager
{
	public:
		explicit CResourceManager()
		{

		}

		virtual ~CResourceManager()
		{

		}

		const Resource& get(Enum name) const
		{
			return m_resources.at(name);
		}

	protected:
		void addResource(Enum name, const std::string& filePath)
		{
			Resource res;
			res.loadFromFile(filePath);
			m_resources.insert(std::make_pair(name, res));
		}

	private:
		std::map <Enum, Resource> m_resources;

};

#endif
