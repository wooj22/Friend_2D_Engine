

/* GameObject Cycle */
virtual void Awake() {};           // 오브젝트가 생성될 때, 생성자 이후
virtual void SceneStart() {};      // Scene의 Start -> Update중 SceneStart() 호출 보장 x
virtual void Update() {};          // Scene의 Update
virtual void Destroyed() {};       // Scene의 Exit, GameObject Delete

/* Component Cycle */
virtual void OnEnable() = 0;	   // 컴포넌트 활성화시
virtual void OnDestroy() = 0;	   // 컴포넌트 or 게임오브젝트 파괴시

/* script component cycle */
void OnEnable() override {}        // 컴포넌트 활성화시
virtual void Awake() {}            // 오브젝트의 모든 컴포넌트가 생성된 직후 시점 1회 호출
virtual void Start() {}            // Awake() 이후 시점 1회 호출
virtual void Update() {}           // 프레임 단위 반복 호출
virtual void FixedUpdate() {}      // 물리 업데이트 0.02f 보장 반복 호출
void OnDestroy() override {}       // 컴포넌트 or 오브젝트 소멸 시점