#pragma once
#include "en/System.hpp"
#include "en/EventSubscriber.hpp"
#include "FrameData.hpp"
#include "core/containers/StaticArray.hpp"
#include "sx/math.h"
#include "io/Window.hpp"

namespace ari::en
{
	class Camera;
	class BoxShape;
	class Node3D;

	class SceneSystem: 
		public System,
		public EventSubscriber<events::OnComponentAssigned<Camera>>,
		public EventSubscriber<events::OnComponentRemoved<Camera>>
	{
	public:

		//! Constructor
		SceneSystem();

		//! Destructor
		~SceneSystem();

		void Update(World* _world, const float& _elapsed, UpdateState::Enum _state) override;
		void Configure(World* p_world) override;
		void Unconfigure(World* _world) override;
		bool NeedUpdateOn(UpdateState::Enum _state) override;

		void Receive(World* world, const events::OnComponentAssigned<Camera>& event) override;
		void Receive(World* world, const events::OnComponentRemoved<Camera>& event) override;

		io::WindowHandle		TargetWindow;

	protected:

		Camera		*	m_pActiveCamera;
		core::StaticArray<FrameData, 3>	
						m_aFrameData;
		int				m_FrameDataTurnIndex = 0;
		FrameData	*	m_pFrameDataUnused,			// This is the unused frame data pointers
					*	m_pFrameDataTransforms,		// This is the transform calculated nodes
					*	m_pFrameDataVisible;		// This is the visible nodes that must be rendered.

		void CalcTransform(Node3D* node, Node3D* parent);

	}; // SceneSystem
	
} // ari::en
