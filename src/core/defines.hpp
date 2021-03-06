#pragma once

#include <cstdint>
#include "Types.hpp"
#include "HandleManager.hpp"
#include "string/StringHash.hpp"

#define ARI_HANDLE(_name) \
struct _name \
{ \
    uint32_t Handle = ari::core::aInvalidHandle; \
	uint32_t Index = ari::core::aInvalidHandle; \
	bool IsValid() \
	{ \
		if (Handle == ari::core::aInvalidHandle || Index == ari::core::aInvalidHandle) \
			return false; \
		return ari::core::HandleManager<_name>::IsHandleValid(Handle); \
	} \
};

#include "net/Serialize.hpp"

//------------------------------------------------------------------------------
#define ARI_COMPONENT(_name) \
static const uint32_t Id; \
static bool IsRegisteredWithComponentManager; \
virtual uint32_t GetId() { return _name::Id; } \
virtual uint32_t GetBaseId() { return _name::Id; } \
static ari::en::ComponentHandle<void> CreateComponent(ari::en::World* _world); \
static void DisposeComponent(ari::en::World* _world, \
							const ari::en::ComponentHandle<void>& _cmp); \
static void DeleteComponent(const ari::en::ComponentHandle<void>& _cmp); \
static void AddComponent(ari::en::World* _world, \
	const ari::en::EntityHandle& _entity, ari::en::ComponentHandle<void> cmp); \
template <typename Stream> \
inline static bool Serialize(Stream& stream, void* obj, const int& member_index = -1) \
{ \
	return ari::net::Serialize<_name, Stream>(stream, *((_name*)obj), member_index); \
} \
static bool IsDiff(void* clone, void* obj, int index);

//------------------------------------------------------------------------------
#define ARI_COMPONENT_IMP(_name) \
const uint32_t _name::Id = COMPILE_TIME_CRC32_STR(#_name); \
bool _name::IsRegisteredWithComponentManager = ari::en::ComponentManager::RegisterComponent<_name>(#_name); \
bool _name::IsDiff(void* clone, void* obj, int index) \
{ \
	return ari::en::ComponentManager::IsDiff<_name>(clone, obj, index); \
} \
ari::en::ComponentHandle<void> _name::CreateComponent(ari::en::World* _world) \
{ \
	auto c = _world->CreateComponent<_name>(); \
	return { c.Handle, c.Index, (void*)c.Component }; \
} \
void _name::DisposeComponent(ari::en::World* _world, \
									const ari::en::ComponentHandle<void>& _cmp) \
{ \
	auto h = ari::en::CastComponentHandle<void, _name>(_cmp); \
	_world->DisposeComponent(h); \
} \
void _name::DeleteComponent(const ari::en::ComponentHandle<void>& _cmp) \
{ \
	ari::en::World::DestroyComponent(ari::en::CastComponentHandle<void, _name>(_cmp)); \
} \
void _name::AddComponent(ari::en::World* _world, \
	const ari::en::EntityHandle& _entity, ari::en::ComponentHandle<void> cmp) \
{ \
	ari::en::ComponentHandle<_name> c; \
	c.Handle = cmp.Handle; \
	c.Index = cmp.Index; \
	c.Component = (_name*)cmp.Component; \
	_world->AddComponent(_entity, c); \
} 

//------------------------------------------------------------------------------
#define ARI_COMPONENT_CHILD(_name, _base) \
static const uint32_t Id; \
static bool IsRegisteredWithComponentManager; \
uint32_t GetId() override { return _name::Id; } \
uint32_t GetBaseId() override { return _base::Id; } \
static ari::en::ComponentHandle<void> CreateComponent(ari::en::World* _world); \
static void DisposeComponent(ari::en::World* _world, \
									const ari::en::ComponentHandle<void>& _cmp); \
static void DeleteComponent(const ari::en::ComponentHandle<void>& _cmp); \
static void AddComponent(ari::en::World* _world, \
	const ari::en::EntityHandle& _entity, ari::en::ComponentHandle<void> cmp); \
template <typename Stream> \
inline static bool Serialize(Stream& stream, void* obj, const int& member_index = -1) \
{ \
	return ari::net::Serialize<_name, Stream>(stream, *((_name*)obj), member_index); \
} \
static bool IsDiff(void* clone, void* obj, int index);

//------------------------------------------------------------------------------
#define ARI_COMPONENT_IMP_CHILD(_name, _base) \
const uint32_t _name::Id = COMPILE_TIME_CRC32_STR(#_name); \
bool _name::IsRegisteredWithComponentManager = ari::en::ComponentManager::RegisterComponent<_name>(#_name); \
bool _name::IsDiff(void* clone, void* obj, int index) \
{ \
	return ari::en::ComponentManager::IsDiff<_name>(clone, obj, index); \
} \
ari::en::ComponentHandle<void> _name::CreateComponent(ari::en::World* _world) \
{ \
	auto c = _world->CreateComponent<_name, _base>(); \
	return { c.Handle, c.Index, (void*)c.Component }; \
} \
void _name::DisposeComponent(ari::en::World* _world, \
							const ari::en::ComponentHandle<void>& _cmp) \
{ \
	auto h = ari::en::CastComponentHandle<void, _name>(_cmp); \
	_world->DisposeComponent(h); \
} \
void _name::DeleteComponent(const ari::en::ComponentHandle<void>& _cmp) \
{ \
	ari::en::World::DestroyComponent<_name, _base>(ari::en::CastComponentHandle<void, _name>(_cmp)); \
} \
void _name::AddComponent(ari::en::World* _world, \
	const ari::en::EntityHandle& _entity, ari::en::ComponentHandle<void> cmp) \
{ \
	ari::en::ComponentHandle<_name> c; \
	c.Handle = cmp.Handle; \
	c.Index = cmp.Index; \
	c.Component = (_name*)cmp.Component; \
	_world->AddDerivedComponent<_name, _base>(_entity, c); \
} \

// ARI_MESSAGE_FACTORY_START
//------------------------------------------------------------------------------
#define ARI_MESSAGE_FACTORY_START( factory_class, num_message_types )																	\
                                                                                                                                        \
    class factory_class : public yojimbo::MessageFactory                                                                                \
    {                                                                                                                                   \
		ari::en::World*	m_pWorld;																										\
		ari::net::ClientSystem* m_pClient;																								\
    public:                                                                                                                             \
        factory_class( yojimbo::Allocator & allocator, ari::en::World* pWorld, ari::net::ClientSystem* pClient ):						\
			MessageFactory( allocator, num_message_types ),																				\
			m_pWorld(pWorld), m_pClient(pClient)	{}																					\
        yojimbo::Message * CreateMessageInternal( int type )                                                                            \
        {                                                                                                                               \
            yojimbo::Message * message;                                                                                                 \
            yojimbo::Allocator & allocator = GetAllocator();                                                                            \
            (void) allocator;                                                                                                           \
            switch ( type )                                                                                                             \
            {                                                                                                                           \
				case 0: /* Create entity */																								\
				{																														\
					auto msg = YOJIMBO_NEW( allocator, CreateEntityMessage );                                                           \
                    if ( !msg )																											\
                        return NULL;                                                                                                    \
					msg->World = m_pWorld;																								\
					msg->client_system = m_pClient;																						\
                    SetMessageType( msg, 0 );																							\
                    return msg;																											\
				}																														\
				case 1: /* Update entity */																								\
				{																														\
					auto msg = YOJIMBO_NEW( allocator, UpdateEntityMessage );                                                           \
                    if ( !msg )																											\
                        return NULL;                                                                                                    \
					msg->client_system = m_pClient;																						\
                    SetMessageType( msg, 1 );																							\
                    return msg;																											\
				}																														\

