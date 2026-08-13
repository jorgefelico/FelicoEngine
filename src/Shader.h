#pragma once

namespace FelicoEngine {
	class Shader {
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void use() const;

		private:
			unsigned int m_ID;
			unsigned int m_vertShader;
			unsigned int m_fragShader;
			void createVertShader(const char* vertPath);
			void createFragShader(const char* fragPath);
			void createProgram();
	};
}