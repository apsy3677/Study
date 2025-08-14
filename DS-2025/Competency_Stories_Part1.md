# Competency Stories (STARR Format)

## 1. Conflict Resolution

### Story 1: Token-based Licensing System Conflict (Synopsys)

**Situation**: "At Synopsys, I was implementing the new FAST token-based licensing system for our formal verification tools. Different application teams had strong disagreements about their token allocation. Teams responsible for higher-complexity apps like FPV and DPV felt their applications weren't being allocated enough tokens relative to simpler apps like FCA. Meanwhile, the FCA and AEP teams were concerned that their users would be disadvantaged by any token increase."

**Task**: "As the technical lead, I needed to design a token allocation system that fairly represented the value and computational resources of each application while addressing the concerns of all product teams."

**Action**: "I recognized this was both a technical and organizational challenge. First, I analyzed the computational requirements and customer value of each application to establish objective baselines. I organized discussions with each product team to understand their specific concerns and gathered data on actual usage patterns. I then proposed a tiered token allocation based on app complexity: 1 token per 12 workers for simpler apps like FCA and AEP, 3 tokens for medium-complexity apps like CC and FuSa, 6 tokens for complex apps like FPV, and 12 tokens for DPV with its 4 workers. To address concerns about fairness, I implemented detailed telemetry to measure actual resource consumption versus token allocation, which would allow us to adjust the model based on real-world data."

**Result**: "We successfully implemented the graduated token allocation system with buy-in from all teams. The data-driven approach helped demonstrate that the token allocations fairly represented both resource usage and customer value. The system also included specific token requirements for Assertion IP (AIP) usage. This comprehensive approach resulted in a 25-30% improvement in overall license utilization."

**Reflection**: "This experience reinforced that technical solutions often require navigating organizational dynamics. By using objective data and creating transparency around the decision-making process, we built trust with the product teams. The telemetry system also gave us the ability to continuously improve the token allocation model based on real usage patterns rather than just initial assumptions."

### Story 2: OneDrive Catalog SKU Filtering (Microsoft)

**Situation**: "At Microsoft, we discovered that unsupported SKUs were being exposed in the OneDrive upsell experience, leading to high-severity incidents when customers purchased incompatible subscriptions."

**Task**: "I needed to implement catalog filtering, but this created tension with the marketing team who wanted to maximize subscription options shown to users."

**Action**: "I arranged a meeting with both engineering and marketing stakeholders to understand the competing priorities. The marketing team was concerned about reducing conversion rates, while engineering was focused on service reliability. I proposed a data-driven approach, analyzing which SKUs were causing the most support issues versus their conversion value. I then designed a whitelisting system that could be controlled dynamically, allowing for gradual implementation rather than an immediate reduction."

**Result**: "The solution satisfied both teams by improving service reliability while allowing controlled testing of SKUs. Incidents related to incompatible subscriptions dropped by 95%, while the ability to dynamically control the whitelist allowed marketing to safely experiment with offerings. This approach strengthened the relationship between our teams."

**Reflection**: "This experience showed me the importance of finding win-win solutions when facing conflicting priorities. By focusing on shared goals (customer satisfaction) and implementing flexible technical solutions, we were able to bridge different organizational perspectives."

## 2. Perseverance

### Story 1: Web Editor Performance Optimization (Adobe)

**Situation**: "At Adobe, enterprise customers were reporting that the AEM Web Editor would freeze or become extremely slow when editing very large documents, threatening several major client relationships."

**Task**: "I was tasked with resolving these performance issues, which had persisted despite multiple previous attempts by other engineers."

**Action**: "I began by conducting extensive profiling to identify bottlenecks, discovering that the editor was attempting to render the entire document at once. Initial attempts at optimization provided only modest improvements. Rather than giving up, I continued exploring more radical solutions. After three weeks of testing different approaches, I proposed a complete redesign of the rendering pipeline to implement lazy loading. This was met with skepticism due to the scope of changes required, but I created a detailed implementation plan and a proof-of-concept that demonstrated the potential performance gains."

**Result**: "After six weeks of determined effort and multiple iterations, we implemented the lazy loading solution, reducing loading times by 60% for large documents. This not only resolved the immediate customer complaints but became a selling point for the product, as it could now handle significantly larger documents than competing solutions."

**Reflection**: "This challenge taught me that sometimes the right solution requires a fundamental rethinking of the approach rather than incremental improvements. Persistence in exploring alternatives and building evidence to support bold changes was key to success."

### Story 2: PowerPoint Recording Studio Enhancements (Microsoft)

**Situation**: "The PowerPoint Recording Studio feature had potential but was underutilized, with complex technical limitations preventing several requested capabilities like background blur and customizable Cameo."

**Task**: "I was leading the effort to enhance the Recording Studio with these capabilities, despite significant technical hurdles in the video processing pipeline."

**Action**: "Initial attempts to implement background blur faced performance issues that caused dropped frames and poor user experience. Instead of scaling back our ambitions, I spent nights researching alternative algorithms and testing different approaches. After several failed attempts, I discovered we could leverage hardware acceleration in a novel way. This required rewriting significant portions of the video pipeline three times before we found the right balance of quality and performance."

**Result**: "After four months of persistent effort, we successfully delivered all planned enhancements. The improvements resonated strongly with users, increasing monthly active users from 1.5M to 4.2M, with 1.2M specifically using the Cameo feature that had been the most challenging to implement."

**Reflection**: "This experience reinforced that breakthrough features often require pushing through multiple failures. By maintaining focus on the end-user value and being willing to restart when necessary, we ultimately delivered capabilities that dramatically improved the product."

## 3. Adaptability

### Story 1: RIBS to Hyperdrive Migration (Adobe)

**Situation**: "Adobe was transitioning from the legacy RIBS build system to the new Hyperdrive environment, requiring significant changes to how Adobe Elements was built and deployed."

**Task**: "I was responsible for migrating the Elements product line to Hyperdrive while ensuring no regression in functionality or release timelines."

**Action**: "The migration proved more complex than initially anticipated, with undocumented dependencies in the legacy system. I had to quickly learn the new Hyperdrive system while simultaneously discovering and documenting the intricacies of our existing build processes. When the initial migration approach failed due to compatibility issues, I rapidly pivoted to a hybrid approach, redesigning our CI/CD pipelines to create independent bundles that could be built and tested in parallel."

**Result**: "Despite the unexpected challenges, we successfully completed the migration ahead of schedule. The new approach not only met the migration requirements but delivered additional benefits, reducing product installation time by 50% on average due to the improved bundling structure."

**Reflection**: "This project taught me the value of remaining flexible when facing evolving requirements and technical constraints. By embracing the need to adapt rather than forcing the original plan, we discovered a better approach that delivered unexpected benefits."

### Story 2: Stream 2.0 Video Integration (Microsoft)

**Situation**: "Microsoft was transitioning from Stream Classic to Stream 2.0, requiring integration with Office applications to enable video insertion and playback from SharePoint/OneDrive."

**Task**: "I needed to build the Excel video playback module, but midway through development, the Stream 2.0 API underwent significant changes to accommodate new security requirements."

**Action**: "Rather than waiting for the API to stabilize or pushing back on timeline expectations, I adapted our approach. I designed a flexible adapter layer that could accommodate the changing API while allowing the rest of the playback module development to proceed in parallel. I maintained daily communication with the Stream team to stay ahead of changes and proactively adjusted our implementation."

**Result**: "Despite the shifting requirements, we delivered the video playback functionality on schedule. The adapter approach we developed became a pattern used by other Office applications integrating with Stream 2.0, streamlining their implementation process as well."

**Reflection**: "This experience highlighted that adaptability isn't just about reacting to change, but anticipating and designing for it. Building flexibility into our architecture from the beginning enabled us to navigate uncertainty without compromising delivery timelines."
