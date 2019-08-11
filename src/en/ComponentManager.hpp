#pragma once
#if ARI_NET
#include "yojimbo.h"
#endif

namespace ari::en
{
	struct World;

	class ComponentManager
	{
		struct ComponentData
		{
			ComponentHandle<void>(*createFn)(World*) = nullptr;
#if ARI_NET
			bool(*serializeFn)(yojimbo::WriteStream&, void*) = nullptr;
			bool(*deserializeFn)(yojimbo::ReadStream&, void*) = nullptr;
			bool(*serializeMeasureFn)(yojimbo::MeasureStream&, void*) = nullptr;
#endif
		};

	public:

		template<typename T>
		static bool RegisterComponent()
		{
			if (!m_mComponentsData)
			{
				m_mComponentsData = core::Memory::New<core::Map<uint32_t, ComponentData>>();
			}
			ComponentData data;
			data.createFn = T::CreateComponent;
#if ARI_NET
			data.serializeFn = &T::Serialize;
			data.deserializeFn = &T::Serialize;
			data.serializeMeasureFn = &T::Serialize;
#endif
			m_mComponentsData->Add(T::Id, data);
			return true;
		}

		static ComponentHandle<void> CreateComponent(uint32_t Id, World* pWorld)
		{
			return (*m_mComponentsData)[Id].createFn(pWorld);
		}

	private:

		static core::Map<uint32_t, ComponentData>*	m_mComponentsData;

	};

} // namespace ari::en
