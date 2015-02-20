namespace sbol {
	class Identified {
		string identity;
		string persistent_identity;
	public:
		void set_values(int, int);
		int area() { return width*height; }
	};
}